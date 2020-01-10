#include "MoveTimed.h"

MoveTimed::MoveTimed(Chassis* chassis , int time, double power): chassis(chassis){
    AddRequirements({chassis});
    desiredTime = time;
    this->power = power;
}

void MoveTimed::Initialize(){
    startTime = frc::Timer::GetFPGATimestamp(); 
    startAngle = chassis->getYaw();
}

void MoveTimed::Execute() {
  chassis->drive(power, startAngle);
}

void MoveTimed::End(bool interrupted){
  chassis->drive(0,startAngle);
}

bool MoveTimed::IsFinished(){
    return frc::Timer::GetFPGATimestamp() - startTime > desiredTime;
}