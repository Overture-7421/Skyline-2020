#include "Chassis.h"
#include "commands/TeleopDrive/TeleopDrive.h"

Chassis::Chassis(){
    gyro.Reset();
    gyro.ZeroYaw();
    gyro.ResetDisplacement();
}

void Chassis::arcadeDrive(double linear, double angular){
    differentialDrive.ArcadeDrive(linear, angular);
    frc::SmartDashboard::PutNumber("yaw", gyro.GetYaw());
        frc::SmartDashboard::PutNumber("pitch", gyro.GetPitch());
    frc::SmartDashboard::PutNumber("roll", gyro.GetRoll());
        frc::SmartDashboard::PutNumber("heading", gyro.GetFusedHeading());


}

void Chassis::tankDrive(double leftSpeed, double rightSpeed){
    differentialDrive.TankDrive(leftSpeed, rightSpeed);
}

double Chassis::getYaw(){
    return gyro.GetYaw();
}



void Chassis::Ramsete(frc::Trajectory target) {
    
   differentialDrive.TankDrive(leftPID.Calculate(leftEncoder.GetRate()) , rightPID.Calculate(rightEncoder.GetRate()));
    frc::Rotation2d gyroAngle{units::degree_t(-gyro.GetAngle())};
    // pose = odometry.Update(gyroAngle, units::meter_t(leftEncoder.GetDistance()),
    //  units::meter_t(rightEncoder.GetDistance()));

     ChassisSpeeds speeds = ramsete.Calculate(pose, targetTrajectory.Sample(2_s));
     DifferentialDriveWheelSpeeds wheelsSpeed = kinematis.ToWheelSpeeds(speeds);
    leftPID.SetSetpoint(double_t(wheelsSpeed.left));
    rightPID.SetSetpoint(double_t(wheelsSpeed.right));
}

void Chassis::TankDrive(double l, double r) {
    this->differentialDrive.TankDrive(l,r);
}
