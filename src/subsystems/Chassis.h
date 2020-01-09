#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
using namespace ctre::phoenix::motorcontrol::can;
using namespace ctre::phoenix::motorcontrol;

class Chassis : public frc2::SubsystemBase {
 public:
  Chassis();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;

 private:
  VictorSPX leftMotor {1};
  VictorSPX rightMotor {2};
  VictorSPX leftMotor1 {3};
  VictorSPX rightMotor1 {4};
};