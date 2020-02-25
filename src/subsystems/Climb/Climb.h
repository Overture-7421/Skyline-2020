#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <frc/Timer.h>
#include "Constants.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/SlewRateLimiter.h>
#include <frc/DigitalInput.h>
#include <frc/Counter.h>
#include <frc/DigitalGlitchFilter.h>
#include <frc/Relay.h>
#include <units/units.h>
using namespace ctre::phoenix::motorcontrol::can;
using namespace ctre::phoenix::motorcontrol;

class Climb : public::frc2::SubsystemBase
{
public:
    Climb();
    void climb();

private:
    WPI_VictorSPX climbMotor1 {3};
    WPI_VictorSPX climbMotor2 {5};
    WPI_VictorSPX climbMotor3 {6};
};