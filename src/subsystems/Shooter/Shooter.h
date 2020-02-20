
#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <frc/Timer.h>

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

  WPI_TalonSRX ShooterMaster {7};
  WPI_VictorSPX ShooterR1 {8}; 
  WPI_VictorSPX ShooterL2 {10};
  WPI_VictorSPX ShooterL1 {9};

  std::shared_ptr<nt::NetworkTable> visionTable = nt::NetworkTableInstance::GetDefault().GetTable("chameleon-vision");

  double rps = 0.0;
  double pulsesPerRev = 4096/4;
  double targetWidth = 0;
  double tolerance = 5;
  const double timeToStableRPS = 1; //Seconds
  double lastTimeStable = frc::Timer::GetFPGATimestamp();
  bool lastOnTargetState = false;
};
