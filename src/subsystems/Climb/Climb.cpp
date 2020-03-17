#include "Climb.h"

Climb::Climb() {
    climbMotor1.SetInverted(true);
    climbMotor1.SetNeutralMode(NeutralMode::Coast);
    climbMotor3.SetNeutralMode(NeutralMode::Coast);
    climbMotor2.SetNeutralMode(NeutralMode::Brake);
}

void Climb::climb(double velocity) {

    if(velocity > 0){
        climbMotor1.Set(ControlMode::PercentOutput, velocity);
        climbMotor3.Set(ControlMode::PercentOutput, 0);
    }else if(velocity < 0){
        climbMotor3.Set(ControlMode::PercentOutput, velocity);
        climbMotor1.Set(ControlMode::PercentOutput, 0);  
    }else{
        climbMotor1.Set(ControlMode::PercentOutput, 0);  
        climbMotor3.Set(ControlMode::PercentOutput, 0);
    }
//    climbMotor2.Set(ControlMode::PercentOutput, velocity);
}

void Climb::winch(double velocity) {
    climbMotor2.Set(ControlMode::PercentOutput, velocity);
}  