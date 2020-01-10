#include "MoveAngularTimed.h"

MoveAngularTimed::MoveAngularTimed(Chassis* chassis , double angle): chassis(chassis){
    AddRequirements({chassis});
    this->angle = angle;
}

void MoveAngularTimed::Initialize(){

}

void MoveAngularTimed::Execute() {
  chassis->drive(0, angle);
}

void MoveAngularTimed::End(bool interrupted){
  chassis->drive(0,0);
}

bool MoveAngularTimed::IsFinished(){
    return std::abs(chassis->getYaw()-angle) < 1;
}
