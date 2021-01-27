//
// Created by ajahueym on 1/10/21.
//

#ifndef BOTBUSTERS_REBIRTH_ECTOGAZEBOMOTOR_H
#define BOTBUSTERS_REBIRTH_ECTOGAZEBOMOTOR_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <frc/controller/PIDController.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <ntcore.h>

#include <atomic>
#include <memory>

#include "Control/PID/PIDConfig.h"
#include "EctoMotor.h"

class GazeboMotor : public EctoMotor {
   public:
    class UpdateManager {
       public:
        void addGazeboMotor(GazeboMotor* motor);
        void removeGazeboMotor(GazeboMotor* motor);
        static UpdateManager& getInstance() {
            static UpdateManager instance;
            return instance;
        }
        UpdateManager(UpdateManager const&) = delete;
        UpdateManager& operator=(UpdateManager const&) = delete;
        ~UpdateManager();

       private:
        explicit UpdateManager();
        std::thread internalControlUpdateThread;
        std::atomic<bool> runningUpdateThreads{true};
        std::atomic<bool> ntConnected{false};
        std::vector<GazeboMotor*> createdGazeboMotors;
        std::mutex updateMutex, nextToAccessMutex, lowPriorityMutex;
    };

    GazeboMotor(const std::string& robot, const std::string& motor);

    void factoryReset();

    void setLimitSwitchPolarity(bool switchPolarity);

    std::string getFirmwareVersion() const;

    void invertMotor(bool state);

    bool isMotorInverted() const;

    void invertSensor(bool state);

    bool isSensorInverted() const;

    void setPIDConfig(const PIDConfig& pidConfig, int profileSlot = 0);

    void enableBrakingOnIdle(bool state);

    void enableCurrentLimit(bool state);

    void setMotorCurrentLimit(double current);

    void setClosedLoopOutputRange(double minimum, double maximum);

    void setClosedLoopRampRate(double rampRate);

    void setOpenLoopRampRate(double rampRate);

    double getOutputPercent() const;

    void setSensorPosition(double position);

    double getTemperature() const;

    double getCurrent() const;

    double getVoltage() const;

    void setEncoderCodesPerRev(int codes);

    int getEncoderCodesPerRev() const;

    void setArbitraryFeedForward(double feedForward);

    void disable();

    bool isDisabled() const;

    void setAnalogSensorOffset(double analogVoltageOffset);

    ~GazeboMotor();

   protected:
    double getRawAnalogPosition() const;

    double getPotPosition() const;

    double getPotVelocity() const;

    double getQuadPosition() const;

    double getQuadVelocity() const;

    void setVoltageOutput(double voltage);

    void setMotorOutputByCurrent(double amps);

    void setOutputPercent(double value);

    void setPositionSetpoint(double position);

    void setVelocitySetpoint(double velocity);

    void setPotAsClosedLoopSource();

    void setQuadAsClosedLoopSource();

   private:
    bool isInClosedLoop() const;
    double getRawWrappedPotPosition() const;
    static int ectoGazeboId;
    UpdateManager& updateManager = GazeboMotor::UpdateManager::getInstance();
    std::shared_ptr<nt::NetworkTable> motorTable;
    nt::NetworkTableEntry positionEntry;
    nt::NetworkTableEntry velocityEntry;
    nt::NetworkTableEntry voltageEntry;
    std::mutex pidMutex;
    bool motorInverted = false;
    bool sensorInverted = false;
    bool disabled = false;
    frc2::PIDController controller{0.0, 0.0, 0.0, units::millisecond_t(20)};
    double minOutput = 1.0, maxOutput = -1.0;
    double arbitraryFeedForward = 0.0;
    int encoderCodes = 1.0;
    double quadPositionOffset = 0.0;
    double potPositionOffset = 0.0;
};

#endif  //BOTBUSTERS_REBIRTH_ECTOGAZEBOMOTOR_H
