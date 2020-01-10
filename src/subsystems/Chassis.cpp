#include "Chassis.h"

Chassis::Chassis(){

}

void Chassis::Periodic(){
    differentialDrive.ArcadeDrive(linear , angular);
    frc::SmartDashboard::PutNumber("Left Encoder",leftEncoder.Get());
    frc::SmartDashboard::PutNumber("Right Encoder", rightEncoder.Get());
}

void Chassis::drive(double linear, double angular){
    this->linear = linear;
    this->angular = angular;
}

