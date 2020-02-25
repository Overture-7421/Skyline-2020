#include "Climb.h"

Climb::Climb() {
    //nuthin
}

void Climb::climb() {
    climbMotor1.Set(ControlMode::PercentOutput, 0.1);
    climbMotor2.Set(ControlMode::PercentOutput, 0.1);
    climbMotor3.Set(ControlMode::PercentOutput, 0.1);
}
