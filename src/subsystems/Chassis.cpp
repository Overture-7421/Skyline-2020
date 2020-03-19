#include "Chassis.h"
#include "commands/TeleopDrive/TeleopDrive.h"

Chassis::Chassis()
{
    rightMaster.ConfigFactoryDefault();
    leftMaster.ConfigFactoryDefault();
    
    gyro.Reset();
    gyro.ZeroYaw();
    gyro.ResetDisplacement();

    frc::SmartDashboard::PutData("Chassis/Chassis", this);
    rightMaster.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
    leftMaster.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
    
    rightMaster.ConfigSelectedFeedbackCoefficient(1.0 / 4.0);
    leftMaster.ConfigSelectedFeedbackCoefficient(1.0 / 4.0);

    rightMotor1.Follow(rightMaster);
    rightMotor2.Follow(rightMaster);

    leftMotor1.Follow(leftMaster);
    leftMotor2.Follow(leftMaster);

    rightMaster.ConfigOpenloopRamp(ChassisMap::RAMP_RATE);
    leftMaster.ConfigOpenloopRamp(ChassisMap::RAMP_RATE);
    rightMaster.SetInverted(true);
    rightMotor1.SetInverted(true);
    rightMotor2.SetInverted(true);
    rightMaster.ConfigPeakCurrentLimit(ChassisMap::peakCurrentLimit);
    rightMaster.ConfigContinuousCurrentLimit(ChassisMap::continuousCurrentLimit);
    leftMaster.ConfigContinuousCurrentLimit(ChassisMap::continuousCurrentLimit);
    rightMaster.ConfigPeakCurrentLimit(ChassisMap::peakCurrentLimit);
    leftMaster.SetSelectedSensorPosition(0);
    rightMaster.SetSelectedSensorPosition(0);
    leftMaster.SetNeutralMode(NeutralMode::Brake);
    rightMaster.SetNeutralMode(NeutralMode::Brake);
    rightMotor1.SetNeutralMode(NeutralMode::Brake);
    rightMotor2.SetNeutralMode(NeutralMode::Brake);
    leftMotor1.SetNeutralMode(NeutralMode::Brake);
    leftMotor2.SetNeutralMode(NeutralMode::Brake);
}

void Chassis::Periodic()
{
    frc::SmartDashboard::PutNumber("Chassis/ X", double_t(odometry.GetPose().Translation().X()));
    frc::SmartDashboard::PutNumber("Chassis/ Y", double_t(odometry.GetPose().Translation().Y()));
    frc::SmartDashboard::PutNumber("Chassis/ yaw", -gyro.GetYaw());
    frc::SmartDashboard::PutNumber("Chassis/ pitch", -gyro.GetRoll());
    frc::SmartDashboard::PutNumber("Chassis/ roll", gyro.GetRoll());
    frc::SmartDashboard::PutNumber("Chassis/ heading", -gyro.GetFusedHeading());
    frc::SmartDashboard::PutNumber("Chassis/ Left Position", leftMaster.GetSelectedSensorPosition());
    frc::SmartDashboard::PutNumber("Chassis/ Right Position", rightMaster.GetSelectedSensorPosition());
    frc::SmartDashboard::PutNumber("Chassis/ Left Speed", leftMaster.GetSelectedSensorVelocity());
    frc::SmartDashboard::PutNumber("Chassis/ Right Speed", rightMaster.GetSelectedSensorVelocity());
    frc::SmartDashboard::PutNumber("Chassis/ Left Master Current", leftMaster.GetSupplyCurrent());
    frc::SmartDashboard::PutNumber("Chassis/ Right Master Current", rightMaster.GetSupplyCurrent());
    frc::Rotation2d gyroRot2d = frc::Rotation2d(units::degree_t(-gyro.GetAngle()));
    odometry.Update(gyroRot2d, units::meter_t(leftMaster.GetSelectedSensorPosition() * ChassisMap::ENC_METER_PER_PULSE),
                    units::meter_t(rightMaster.GetSelectedSensorPosition() * ChassisMap::ENC_METER_PER_PULSE));
}
frc::DifferentialDriveWheelSpeeds Chassis::getWheelSpeeds()
{
    frc::DifferentialDriveWheelSpeeds wheelSpeeds;
    wheelSpeeds.right = units::meters_per_second_t(rightMaster.GetSelectedSensorVelocity() * ChassisMap::ENC_METER_PER_PULSE / 0.1);
    wheelSpeeds.left  = units::meters_per_second_t(leftMaster.GetSelectedSensorVelocity() * ChassisMap::ENC_METER_PER_PULSE / 0.1);
    return wheelSpeeds;
}
void Chassis::arcadeDrive(double linear, double angular)
{
    rightMaster.Set(linear + angular);
    leftMaster.Set(linear - angular);
}

void Chassis::tankDrive(double leftSpeed, double rightSpeed)
{
    rightMaster.Set(rightSpeed);
    leftMaster.Set(leftSpeed);
}

void Chassis::voltageDrive(units::volt_t leftvoltage, units::volt_t rightVoltage)
{
    rightMaster.SetVoltage(rightVoltage);
    leftMaster.SetVoltage(leftvoltage);
    frc::SmartDashboard::PutNumber("RightVoltage", double_t(rightVoltage));
    frc::SmartDashboard::PutNumber("LeftVoltage", double_t(leftvoltage));
}

double Chassis::getYaw()
{
    return gyro.GetYaw();
}

frc::Pose2d Chassis::getPose()
{
    return odometry.GetPose();
}
void Chassis::setRateLimit(bool state)
{
    if (state)
    {
        rightMaster.ConfigOpenloopRamp(ChassisMap::RAMP_RATE);
        leftMaster.ConfigOpenloopRamp(ChassisMap::RAMP_RATE);
    } else{
        rightMaster.ConfigOpenloopRamp(0.0);
        leftMaster.ConfigOpenloopRamp(0.0);
    }
}