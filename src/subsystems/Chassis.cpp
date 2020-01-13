#include "Chassis.h"
#include "commands/TeleopDrive/TeleopDrive.h"

Chassis::Chassis() {
    
    gyro.Reset();
    gyro.ZeroYaw();
    gyro.ResetDisplacement();
    frc::SmartDashboard::PutNumber("kP",ChassisMap::KP);
    frc::SmartDashboard::PutNumber("kI",ChassisMap::KI);
    frc::SmartDashboard::PutNumber("kD",ChassisMap::KD);
    frc::SmartDashboard::PutData("Chassis",this);
}
void Chassis::Periodic() {
    frc::SmartDashboard::PutNumber("X", double_t(odometry.GetPose().Translation().X()));
    frc::SmartDashboard::PutNumber("Y", double_t(odometry.GetPose().Translation().Y()));
    leftPID.SetP(frc::SmartDashboard::GetNumber("kP",0));
    leftPID.SetI(frc::SmartDashboard::GetNumber("kI",0));
    leftPID.SetD(frc::SmartDashboard::GetNumber("kD",0));
    rightPID.SetP(frc::SmartDashboard::GetNumber("kP",0));
    rightPID.SetI(frc::SmartDashboard::GetNumber("kI",0));
    rightPID.SetD(frc::SmartDashboard::GetNumber("kD",0));
}

void Chassis::arcadeDrive(double linear, double angular) {
    differentialDrive.ArcadeDrive(linear, angular);
    frc::SmartDashboard::PutNumber("yaw", gyro.GetYaw());
    frc::SmartDashboard::PutNumber("pitch", gyro.GetPitch());
    frc::SmartDashboard::PutNumber("roll", gyro.GetRoll());
    frc::SmartDashboard::PutNumber("heading", gyro.GetFusedHeading());
    frc::SmartDashboard::PutNumber("Left encoder", leftEncoder.Get());
    frc::SmartDashboard::PutNumber("Right encoder", rightEncoder.Get());
    gyroRot2d = frc::Rotation2d (units::degree_t(-gyro.GetAngle()));
    pose = odometry.Update(gyroRot2d, units::meter_t(leftEncoder.GetDistance()),
    units::meter_t(rightEncoder.GetDistance()));
}

void Chassis::TankDrive(double leftSpeed, double rightSpeed){
    differentialDrive.TankDrive(leftSpeed, rightSpeed);
}

double Chassis::getYaw() {
    return gyro.GetYaw();
}

void Chassis::Ramsete(frc::Trajectory target) {
    
   differentialDrive.TankDrive(leftPID.Calculate(leftEncoder.GetRate()) , rightPID.Calculate(rightEncoder.GetRate()));
    frc::Rotation2d gyroAngle{units::degree_t(-gyro.GetAngle())};
    // pose = odometry.Update(gyroAngle, units::meter_t(leftEncoder.GetDistance()),
    //  units::meter_t(rightEncoder.GetDistance()));

     ChassisSpeeds speeds = ramsete.Calculate(pose, target.States().back());
     DifferentialDriveWheelSpeeds wheelsSpeed = kinematics.ToWheelSpeeds(speeds);
    leftPID.SetSetpoint(double_t(wheelsSpeed.left));
    rightPID.SetSetpoint(double_t(wheelsSpeed.right));
}

