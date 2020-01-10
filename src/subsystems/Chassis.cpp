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
<<<<<<< HEAD

    frc::SmartDashboard::PutNumber("Heading", gyro.GetYaw());
=======
    frc::SmartDashboard::PutNumber("Left Encoder",leftEncoder.Get());
    frc::SmartDashboard::PutNumber("Right Encoder", rightEncoder.Get());
>>>>>>> 4db7c4ba833324fcacbecca3616efcca04476b50
}

void Chassis::drive(double linear, double angle){
    this->linear = linear;
    this->targetangle = angle;
}

double Chassis::getYaw(){
    return gyro.GetYaw();
}


