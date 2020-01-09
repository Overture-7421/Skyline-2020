#include "MoveAngularTimed.h"

MoveAngularTimed::MoveAngularTimed(Chassis* chassis , int time, double power): chassis(chassis){
    AddRequirements({chassis});
    desiredTime = time;
    this->power = power;
}

void MoveAngularTimed::Initialize(){
    startTime = frc::Timer::GetFPGATimestamp(); 
}

void MoveAngularTimed::Execute() {
  chassis->drive(0, power);
}

void MoveAngularTimed::End(bool interrupted){
  chassis->drive(0,0);
}

bool MoveAngularTimed::IsFinished(){
    return frc::Timer::GetFPGATimestamp() - startTime > desiredTime;
}
