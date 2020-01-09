#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/SpeedControllerGroup.h>
using namespace ctre::phoenix::motorcontrol::can;
using namespace ctre::phoenix::motorcontrol;

class Chassis : public frc2::SubsystemBase {
 public:
  Chassis();
  void Periodic() override;
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void drive(double linear, double angular);

 private:
  WPI_VictorSPX leftMotor {1};
  WPI_VictorSPX rightMotor {2};
  WPI_VictorSPX leftMotor1 {3};
  WPI_VictorSPX rightMotor1 {4};

  frc::SpeedControllerGroup left{leftMotor, leftMotor1};
  frc::SpeedControllerGroup right{rightMotor, rightMotor1};
  frc::DifferentialDrive differentialDrive{left, right};

  double linear = 0;
  double angular = 0;
};