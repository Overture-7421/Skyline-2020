#include "Climb.h"

Climb::Climb() {
    climbMotor1.SetInverted(true);
}

void Climb::climb(double velocity) {
   climbMotor1.Set(ControlMode::PercentOutput, velocity);
//    climbMotor2.Set(ControlMode::PercentOutput, velocity);
   climbMotor3.Set(ControlMode::PercentOutput, velocity * 0.5);
}

void Climb::winch(double velocity) {
    climbMotor2.Set(ControlMode::PercentOutput, velocity);
}  