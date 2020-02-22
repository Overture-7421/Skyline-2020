//
// Created by Alberto Jahueyu on 2/18/2020.
//

#include "Feeder.h"

Feeder::Feeder() {
    feederMotor.ConfigOpenloopRamp(0.2);
    feederMotor.SetInverted(true);
}

void Feeder::feed(double output) {
    feederMotor.Set(output);

    if(std::abs(output) > 0.1){
        intakePiston.Set(frc::DoubleSolenoid::kForward);
    }else{
        intakePiston.Set(frc::DoubleSolenoid::kReverse);
    }
}