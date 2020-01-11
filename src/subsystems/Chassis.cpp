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



