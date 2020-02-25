//
// Created by Alberto Jahueyu on 2/18/2020.
//

#include "Feeder.h"

Feeder::Feeder() {
    feederMotor.ConfigOpenloopRamp(0.2);
    //feederMotor.SetInverted(true);
    lowerFeeder(false);
}

void Feeder::feed(double output) {
    feederMotor.Set(output);
}

void Feeder::lowerFeeder(bool lower){
    if(lower){
        intakePiston.Set(frc::DoubleSolenoid::kForward);
    }else{
        intakePiston.Set(frc::DoubleSolenoid::kReverse);
    }
}
