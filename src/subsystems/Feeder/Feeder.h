//
// Created by Alberto Jahueyu on 2/18/2020.
//

#ifndef OVERTUREROBOTCODE_FEEDER_H
#define OVERTUREROBOTCODE_FEEDER_H
#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <Constants.h>
using namespace ctre::phoenix::motorcontrol::can;
using namespace ctre::phoenix::motorcontrol;

class Feeder : public frc2::SubsystemBase {
public:
    explicit Feeder();
    void feed(double output);
private:
    WPI_VictorSPX feederMotor {FeederMap::FEEDER_MOTOR};
};


#endif //OVERTUREROBOTCODE_FEEDER_H