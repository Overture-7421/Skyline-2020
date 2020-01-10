#include "Chassis2.h"

Chassis2::Chassis2(){
    frc::SmartDashboard::PutNumber("Target", 0);
    frc::SmartDashboard::PutNumber("Heading P", 0.01);
    leftEncoder.SetDistancePerPulse(0.000469043);
    rightEncoder.SetDistancePerPulse(0.000469043);
    rightMotor.ConfigOpenLoopRamp(1/3);
    rightMotor1.ConfigOpenLoopRamp(1/3);
    leftMotor.ConfigOpenLoopRamp(1/3);
    leftMotor1.ConfigOpenLoopRamp(1/3);
    c::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
    rc::Translation2d(1_m, 1_m), frc::Translation2d(2_m, -1_m)},
    frc::Pose2d(3_m, 0_m, frc::Rotation2d(0_deg)),
    config
    );
}

void Chassis2::Periodic(){
    frc::Rotation2d gyroAngle{units::degree_t(-gyro.GetAngle())};
    pose = odometry.Update(gyroAngle, units::meter_t(leftEncoder.GetDistance()),
    units::meter_t(rightEncoder.GetDistance()));
    ChassisSpeeds speeds = ramsete.Calculate(pose, targetTrajectory.Sample(2_s));
    DifferentialDriveWheelSpeeds wheelsSpeed = kinematis.ToWheelSpeeds(speeds);
}

void Chassis2::Tankdrive(double leftSpeed, double rightSpeed, bool squareInputs = true){
    differentialDrive.TankDrive(leftSpeed, rightSpeed, squareInputs);
}

void Chassis2::ArcadeDrive(double linear, double angular, bool squareInputs = true){
    differentialDrive.ArcadeDrive(linear, angular, squareInputs);
}

double Chassis2::GetYaw(){
    return gyro.GetYaw();
}

void Chassis2::updateSmartDashboard() {
    frc::SmartDashboard::PutNumber("X", double_t(odometry.GetPose().Translation().X()));
    frc::SmartDashboard::PutNumber("Right Encoder", rightEncoder.GetRate());
    frc::SmartDashboard::PutNumber("Left encoder", leftEncoder.GetRate());
    frc::SmartDashboard::PutNumber("Y", double_t(odometry.GetPose().Translation().Y()));
    frc::SmartDashboard::PutNumber("Heading", gyro.GetYaw());
    frc::SmartDashboard::PutNumber("Left Encoder",leftEncoder.Get());
    frc::SmartDashboard::PutNumber("Right Encoder", rightEncoder.Get());
}

void Chassis2::UpdateBoard() {
    frc::SmartDashboard::PutNumber("X", double_t(odometry.GetPose().Translation().X()));
    frc::SmartDashboard::PutNumber("Right Encoder", rightEncoder.GetRate());
    frc::SmartDashboard::PutNumber("Left encoder", leftEncoder.GetRate());
    frc::SmartDashboard::PutNumber("Y", double_t(odometry.GetPose().Translation().Y()));
    frc::SmartDashboard::PutNumber("Heading", gyro.GetYaw());
    frc::SmartDashboard::PutNumber("Left Encoder",leftEncoder.Get());
    frc::SmartDashboard::PutNumber("Right Encoder", rightEncoder.Get());
}
