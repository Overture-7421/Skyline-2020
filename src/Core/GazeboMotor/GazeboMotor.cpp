//
// Created by ajahueym on 1/10/21.
//

#include "GazeboMotor.h"

#include <frc/DriverStation.h>
#include <frc/system/plant/DCMotor.h>

#include <algorithm>
#include <cmath>

int GazeboMotor::ectoGazeboId = 0;

GazeboMotor::GazeboMotor(const std::string& robot, const std::string& motor) : EctoMotor(ectoGazeboId++, robot + "/" + motor) {
    static auto ntInstance = nt::NetworkTableInstance::GetDefault();
    ntInstance.AddConnectionListener([this](const nt::ConnectionNotification& notification) {
        if (notification.connected) {
            quadPositionOffset = positionEntry.GetDouble(0.0);
        }
    },
                                     false);

    motorTable = ntInstance.GetTable(robot)->GetSubTable(motor);
    positionEntry = motorTable->GetEntry("Position");
    velocityEntry = motorTable->GetEntry("Velocity");
    voltageEntry = motorTable->GetEntry("Voltage");
    potPositionOffset = 0.0;
    updateManager.addGazeboMotor(this);

#ifndef SIMULATION
    std::cerr << "Using EctoGazeboMotor in a non simulated project! This is for Gazebo and Simulations! Motor Name: " << robot + "/" + motor << "\n";
#endif
}

void GazeboMotor::factoryReset() {
    motorInverted = false;
    sensorInverted = false;
    encoderCodes = 1;
    quadPositionOffset = positionEntry.GetDouble(0.0);
    potPositionOffset = 0.0;
    voltageEntry.SetDouble(0.0);
    controller = {0.0, 0.0, 0.0, units::millisecond_t(20)};
}

void GazeboMotor::setLimitSwitchPolarity(bool switchPolarity) {
    throw std::runtime_error("setLimitSwitchPolarity not implemented for EctoGazeboMotor " + getName());
}

std::string GazeboMotor::getFirmwareVersion() const {
    return "1.0.1";
}

void GazeboMotor::setVoltageOutput(double voltage) {
    static const frc::DriverStation& driverStation = frc::DriverStation::GetInstance();

    if (!disabled && driverStation.IsEnabled()) {
        double actualValue = (std::abs(voltage) > 12.0 ? std::copysign(12.0, voltage) : voltage) + arbitraryFeedForward;
        actualValue *= (motorInverted ? -1.0 : 1.0);
        bool isClosedLoop = isInClosedLoop();

        bool clampEnabled = minOutput < maxOutput && (minOutput != 1.0 && maxOutput != -1.0);

        if (isClosedLoop && clampEnabled) {
            actualValue = std::clamp(actualValue, minOutput, maxOutput);
        }
        voltageEntry.SetDouble(actualValue);
    } else {
        voltageEntry.SetDouble(0.0);
    }
}

void GazeboMotor::invertMotor(bool state) {
    motorInverted = state;
}

bool GazeboMotor::isMotorInverted() const {
    return motorInverted;
}

void GazeboMotor::invertSensor(bool state) {
    sensorInverted = state;
}

bool GazeboMotor::isSensorInverted() const {
    return sensorInverted;
}

void GazeboMotor::setPIDConfig(const PIDConfig& pidConfig, int profileSlot) {
    std::lock_guard guard(pidMutex);

    controller.SetPID(pidConfig.p, pidConfig.i, pidConfig.d);
    if (pidConfig.continous) {
        controller.EnableContinuousInput(pidConfig.minInput, pidConfig.maxInput);
    }

    if (pidConfig.maxAbsoluteIntegral != -1.0) {
        if (pidConfig.maxAbsoluteIntegral < 0.0) {
            throw std::invalid_argument("PIDConfig given with negative Max Absolute Integral on Gazebo Motor " + getName());
        }
        controller.SetIntegratorRange(0.0, pidConfig.maxAbsoluteIntegral);
    }

    if (pidConfig.clamped) {
        setClosedLoopOutputRange(pidConfig.minOutput, pidConfig.maxOutput);
    }

    if (pidConfig.deadband != 0) {
        // TODO Implement
        std::cerr << "Cannot apply deadband on PID output for EctoGazeboMotor " << getName() << "\n";
    }
}

void GazeboMotor::enableBrakingOnIdle(bool state) {
    std::cerr << "enableBrakingOnIdle not implemented for EctoGazeboMotor " << getName() << "\n";
}

void GazeboMotor::enableCurrentLimit(bool state) {
    std::cerr << "Current limiting Gazebo Motor... (It does absolutely nothing right now)\n";
}

void GazeboMotor::setMotorCurrentLimit(double current) {
    std::cerr << "Setting current limit on Gazebo Motor... (It does absolutely nothing right now)\n";
}

void GazeboMotor::setMotorOutputByCurrent(double amps) {
    std::lock_guard guard(pidMutex);
    controller.SetSetpoint(amps);
}

void GazeboMotor::setClosedLoopOutputRange(double minimum, double maximum) {
    if (minimum >= maximum) {
        std::cerr << "Minimum closed loop output range cant be greater than maximum! Setting not applied on Gazebo Motor " << getName() << "\n";
    } else {
        minOutput = minimum;
        maxOutput = maximum;
    }
}

void GazeboMotor::setClosedLoopRampRate(double rampRate) {
    std::cerr << "setClosedLoopRampRate not implemented for EctoGazeboMotor " << getName() << "\n";
}

void GazeboMotor::setOpenLoopRampRate(double rampRate) {
    throw std::runtime_error("setOpenLoopRampRate not implemented for EctoGazeboMotor " + getName());
}

void GazeboMotor::setOutputPercent(double value) {
    setVoltageOutput(value * 12.0);
}

double GazeboMotor::getOutputPercent() const {
    return getVoltage() / 12.0;
}

void GazeboMotor::setSensorPosition(double position) {
    switch (feedbackMode) {
        case MotorFeedbackMode::None: {
            std::cerr << "Setting sensor position when no Feedback Mode was specified for Gazebo Motor " << getName() << "\n";
            break;
        }
        case MotorFeedbackMode::QuadEncoder: {
            double rawPosition = positionEntry.GetDouble(0.0);
            quadPositionOffset = rawPosition - position;
            break;
        }
        case MotorFeedbackMode::Potentiometer: {
            double rawPosition = getRawWrappedPotPosition();

            if (std::abs(position) > M_PI) {
                throw std::invalid_argument("Magnitude of position cant be greater tha PI using analog sensor on Gazebo Motor " + getName());
            }

            potPositionOffset = rawPosition - position;
            break;
        }
    }
}

void GazeboMotor::setPositionSetpoint(double position) {
    std::lock_guard guard(pidMutex);
    controller.SetSetpoint(position);
}

void GazeboMotor::setVelocitySetpoint(double velocity) {
    std::lock_guard guard(pidMutex);
    controller.SetSetpoint(velocity);
}

double GazeboMotor::getTemperature() const {
    return 30.0;
}

double GazeboMotor::getCurrent() const {
    // TODO Make it so the motor type can be defined through the Gazebo Plugin
    return frc::DCMotor::NEO().Current(units::radians_per_second_t(getVelocity()), units::volt_t(getVoltage())).to<double>();
}

double GazeboMotor::getVoltage() const {
    return voltageEntry.GetDouble(0.0) * (motorInverted ? -1.0 : 1.0);
}

void GazeboMotor::setEncoderCodesPerRev(int codes) {
    encoderCodes = codes;
}

int GazeboMotor::getEncoderCodesPerRev() const {
    return encoderCodes;
}

void GazeboMotor::setArbitraryFeedForward(double feedForward) {
    arbitraryFeedForward = feedForward;
}

void GazeboMotor::disable() {
    setVoltageOutput(0.0);
    disabled = true;
}

bool GazeboMotor::isDisabled() const {
    return disabled;
}

double GazeboMotor::getRawAnalogPosition() const {
    return getRawWrappedPotPosition();
}

double GazeboMotor::getPotPosition() const {
    double position = (getRawWrappedPotPosition() / encoderCodes - potPositionOffset) * (sensorInverted ? -1.0 : 1.0);
    if (std::abs(position) > M_PI) {
        position -= std::copysign(2 * M_PI, position);
    }
    return position;
}

double GazeboMotor::getPotVelocity() const {
    return (velocityEntry.GetDouble(0.0) / encoderCodes) * (sensorInverted ? -1.0 : 1.0);
}

double GazeboMotor::getQuadPosition() const {
    return (positionEntry.GetDouble(0.0) / encoderCodes - quadPositionOffset) * (sensorInverted ? -1.0 : 1.0);
}

double GazeboMotor::getQuadVelocity() const {
    return (velocityEntry.GetDouble(0.0) / encoderCodes) * (sensorInverted ? -1.0 : 1.0);
}

void GazeboMotor::setPotAsClosedLoopSource() {
    feedbackMode = MotorFeedbackMode::Potentiometer;
}

void GazeboMotor::setQuadAsClosedLoopSource() {
    feedbackMode = MotorFeedbackMode::QuadEncoder;
}

void GazeboMotor::setAnalogSensorOffset(double analogVoltageOffset) {
    if (std::abs(analogVoltageOffset) > M_PI) {
        std::cerr << "Analog Sensor Offset magnitude cant be greater than PI, setting not applied, on Gazebo Motor " << getName() << "\n";
    } else {
        potPositionOffset = analogVoltageOffset;
    }
}

bool GazeboMotor::isInClosedLoop() const {
    return controlMode != MotorControlMode::Percent && controlMode != MotorControlMode::Voltage;
    ;
}

double GazeboMotor::getRawWrappedPotPosition() const {
    double rawPosition = positionEntry.GetDouble(0.0);

    double angle = std::copysign(std::fmod(rawPosition, 2 * M_PI), rawPosition);
    if (angle > M_PI) {
        angle -= 2 * M_PI;
    } else if (angle < -M_PI) {
        angle += 2 * M_PI;
    }
    return angle;
}

GazeboMotor::~GazeboMotor() {
    updateManager.removeGazeboMotor(this);

    positionEntry.Delete();
    velocityEntry.Delete();
    voltageEntry.Delete();
}

GazeboMotor::UpdateManager::UpdateManager() {
    static auto ntInstance = nt::NetworkTableInstance::GetDefault();
    ntInstance.AddConnectionListener([this](const nt::ConnectionNotification& notification) {
        if (notification.connected) {
            ntConnected = true;
        }
    },
                                     true);

    internalControlUpdateThread = std::thread([this] {
        static const frc::DriverStation& driverStation = frc::DriverStation::GetInstance();

        const auto start = std::chrono::high_resolution_clock::now();
        double timeoutCounter = 0;
        std::cout << "Gazebo Motor UpdateManager waiting for NetworkTables to connect...\n";
        while (!ntConnected && runningUpdateThreads) {
            timeoutCounter = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();

            if (timeoutCounter > 20.0) {
                std::cerr << "Gazebo Motor UpdateManager couldn't connect to NetworkTables! It wont run...\n";
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        std::cout << "Gazebo Motor UpdateManager connected!\n";

        while (runningUpdateThreads) {
            std::lock_guard lowGuard(lowPriorityMutex);
            std::unique_lock nextToAccess(nextToAccessMutex);
            std::lock_guard updateGuard(updateMutex);

            nextToAccess.unlock();

            for (const auto& motor : createdGazeboMotors) {
                if (!motor->positionEntry.Exists() || !motor->velocityEntry.Exists()) {
                    std::cerr << "Trying to control non existent/invalid Gazebo Motor, either its velocity or position entry doesnt exist! " << motor->getName() << "\n";
                } else {
                    if (motor->isInClosedLoop() && driverStation.IsEnabled()) {
                        std::lock_guard guard(motor->pidMutex);

                        double voltage = 0.0;
                        switch (motor->getControlMode()) {
                            case MotorControlMode::Velocity:
                                voltage = motor->controller.Calculate(motor->getVelocity());
                                break;
                            case MotorControlMode::Position:
                                voltage = motor->controller.Calculate(motor->getPosition());
                                break;
                            case MotorControlMode::Current:
                                voltage = motor->controller.Calculate(motor->getCurrent());
                                break;
                            case MotorControlMode::MotionMagic:
                                throw std::runtime_error("Motion Magic not yet implemented in Gazebo Motor " + motor->getName());
                            case MotorControlMode::Percent:
                            case MotorControlMode::Voltage:
                                throw std::runtime_error("This code is supposed to run in a closed loop control mode! Check EctoGazeboMotor::isInClosedLoop on motor " + motor->getName());
                        }
                        motor->setVoltageOutput(voltage);
                    } else if (!driverStation.IsEnabled()) {
                        motor->setVoltageOutput(0.0);
                    }
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    });
}

void GazeboMotor::UpdateManager::addGazeboMotor(GazeboMotor* motor) {
    std::unique_lock nextGuard(nextToAccessMutex);
    std::lock_guard guard(updateMutex);

    nextGuard.unlock();

    const auto& iterator = std::find(createdGazeboMotors.begin(), createdGazeboMotors.end(), motor);
    if (iterator != createdGazeboMotors.end()) {
        std::cerr << "Tried to add a Gazebo Motor twice to the UpdateManager!\n";
        return;
    }
    createdGazeboMotors.emplace_back(motor);
}

void GazeboMotor::UpdateManager::removeGazeboMotor(GazeboMotor* motor) {
    std::unique_lock nextGuard(nextToAccessMutex);
    std::lock_guard guard(updateMutex);

    nextGuard.unlock();
    const auto& iterator = std::find(createdGazeboMotors.begin(), createdGazeboMotors.end(), motor);
    if (iterator == createdGazeboMotors.end()) {
        std::cerr << "Tried remove a Gazebo Motor that wasn't in UpdateManager!\n";
        return;
    }
    createdGazeboMotors.erase(iterator);
}

GazeboMotor::UpdateManager::~UpdateManager() {
    runningUpdateThreads = false;

    while (!internalControlUpdateThread.joinable()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    internalControlUpdateThread.join();
}
