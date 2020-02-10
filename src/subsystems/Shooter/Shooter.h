
#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc/smartdashboard/SmartDashboard.h>

using namespace ctre::phoenix::motorcontrol::can;
using namespace ctre::phoenix::motorcontrol;

class Shooter : public frc2::SubsystemBase {
 public:
  Shooter();
  
  void setRPS (double rps);
  bool rpsObjectiveReached();
 


  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

 private:
  double pulsesPerRev = 4096/4;
  WPI_TalonSRX ShooterMaster {7};
  WPI_VictorSPX ShooterR1 {8}; 
  WPI_VictorSPX ShooterL1 {9};

  double rps; 
  double tolerance = 2;


};
