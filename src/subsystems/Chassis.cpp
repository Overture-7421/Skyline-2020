#include "Chassis.h"

Chassis::Chassis(){
    frc::SmartDashboard::PutNumber("Heading P", 0.01);
    leftEncoder.SetDistancePerPulse(0.000469043);
    rightEncoder.SetDistancePerPulse(0.000469043);
}

void Chassis::Periodic(){
   
    differentialDrive.ArcadeDrive(linear , angular);
    frc::SmartDashboard::PutNumber("X", double_t(odometry.GetPose().Translation().X()));
    frc::SmartDashboard::PutNumber("Y", double_t(odometry.GetPose().Translation().Y()));
    frc::SmartDashboard::PutNumber("Heading", gyro.GetYaw());
    frc::SmartDashboard::PutNumber("Left Encoder",leftEncoder.Get());
    frc::SmartDashboard::PutNumber("Right Encoder", rightEncoder.Get());
    frc::Rotation2d gyroAngle{units::degree_t(-gyro.GetAngle())};
    pose = odometry.Update(gyroAngle, units::meter_t(leftEncoder.GetDistance()),
     units::meter_t(rightEncoder.GetDistance()));

     
}

void Chassis::drive(double linear, double angular){
    this->linear = linear;
    this->angular = angular;
}

double Chassis::getYaw(){
    return gyro.GetYaw();
}


