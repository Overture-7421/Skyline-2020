#include "Chassis.h"

Chassis::Chassis(){
    frc::SmartDashboard::PutNumber("Heading P", 0.01);

}

void Chassis::Periodic(){
    double error = (targetangle - gyro.GetYaw());

    if(error > 180){
        error -= 360;
    }

    if(error < -180){
        error += 360;
    }

    angular = error * frc::SmartDashboard::GetNumber("Heading P", 0.01);
    differentialDrive.ArcadeDrive(linear , angular);

    frc::SmartDashboard::PutNumber("Heading", gyro.GetYaw());
}

void Chassis::drive(double linear, double angle){
    this->linear = linear;
    this->targetangle = angle;
}

double Chassis::getYaw(){
    return gyro.GetYaw();
}


