#include "Chassis.h"
#include "commands/TeleopDrive/TeleopDrive.h"

Chassis::Chassis() {
    gyro.Reset();
    gyro.ZeroYaw();
    gyro.ResetDisplacement();
    frc::SmartDashboard::PutNumber("Chassis/kP",ChassisMap::KP);
    frc::SmartDashboard::PutNumber("Chassis/kI",ChassisMap::KI);
    frc::SmartDashboard::PutNumber("Chassis/kD",ChassisMap::KD);
    frc::SmartDashboard::PutData("Chassis/Chassis",this);
    leftMaster.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
    rightMaster.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);

    rightMotor1.Follow(rightMaster);
    rightMotor2.Follow(rightMaster);

    leftMotor1.Follow(leftMaster);
    leftMotor2.Follow(leftMaster);

    leftMaster.ConfigOpenloopRamp(0.1);
    rightMaster.ConfigOpenloopRamp(0.1);
}

void Chassis::Periodic() {
    frc::SmartDashboard::PutNumber("Chassis/X", double_t(odometry.GetPose().Translation().X()));
    frc::SmartDashboard::PutNumber("Chassis/Y", double_t(odometry.GetPose().Translation().Y()));
    frc::SmartDashboard::PutNumber("Chassis/yaw", gyro.GetYaw());
    frc::SmartDashboard::PutNumber("Chassis/pitch", gyro.GetPitch());
    frc::SmartDashboard::PutNumber("Chassis/roll", gyro.GetRoll());
    frc::SmartDashboard::PutNumber("Chassis/heading", gyro.GetFusedHeading());
    frc::SmartDashboard::PutNumber("Chassis/Left Position", leftMaster.GetSelectedSensorPosition());
    frc::SmartDashboard::PutNumber("Chassis/Right Position", rightMaster.GetSelectedSensorPosition());
    frc::SmartDashboard::PutNumber("Chassis/Left Speed", leftMaster.GetSelectedSensorVelocity());
    frc::SmartDashboard::PutNumber("Chassis/Right Speed", rightMaster.GetSelectedSensorVelocity());
    frc::SmartDashboard::PutNumber("Chassis/Left Speed Error", leftMaster.GetClosedLoopError());
    frc::SmartDashboard::PutNumber("Chassis/Right Speed Error", rightMaster.GetClosedLoopError());
    frc::SmartDashboard::PutNumber("Chassis/Left Speed Target", leftMaster.GetClosedLoopTarget());
    frc::SmartDashboard::PutNumber("Chassis/Right Speed Target", rightMaster.GetClosedLoopTarget());
    frc::Rotation2d gyroRot2d = frc::Rotation2d (units::degree_t(-gyro.GetAngle()));
    odometry.Update(gyroRot2d, units::meter_t(leftMaster.GetSelectedSensorPosition()),
    units::meter_t(rightMaster.GetSelectedSensorPosition()));
}

void Chassis::arcadeDrive(double linear, double angular) {
    leftMaster.Set(linear + angular);
    rightMaster.Set(linear - angular);
}

void Chassis::tankDrive(double leftSpeed, double rightSpeed){
    leftMaster.Set(leftSpeed);
    rightMaster.Set(rightSpeed);
}

void Chassis::voltageDrive(double leftVoltage, double rightVoltage){
    leftMaster.SetVoltage(units::volt_t(leftVoltage));
    rightMaster.SetVoltage(units::volt_t(rightVoltage));  
}

double Chassis::getYaw() {
    return gyro.GetYaw();
}

void Chassis::Ramsete(frc::Trajectory target) {
    
    // frc::Rotation2d gyroAngle{units::degree_t(-gyro.GetAngle())};
    // // pose = odometry.Update(gyroAngle, units::meter_t(leftEncoder.GetDistance()),
    // //  units::meter_t(rightEncoder.GetDistance()));

    //  ChassisSpeeds speeds = ramsete.Calculate(pose, target.States().back());
    //  DifferentialDriveWheelSpeeds wheelsSpeed = kinematics.ToWheelSpeeds(speeds);
    // leftPID.SetSetpoint(double_t(wheelsSpeed.left));
    // rightPID.SetSetpoint(double_t(wheelsSpeed.right));
}

frc::Pose2d Chassis::getPose() {
    return odometry.GetPose();
}