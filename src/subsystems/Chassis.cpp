#include "Chassis.h"

Chassis::Chassis(){

}

void Chassis::Periodic(){
    differentialDrive.ArcadeDrive(linear , angular);
}

void Chassis::drive(double linear, double angular){
    this->linear = linear;
    this->angular = angular;
}

