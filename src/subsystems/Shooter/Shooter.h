
#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

using namespace ctre::phoenix::motorcontrol::can;
using namespace ctre::phoenix::motorcontrol;

class Shooter : public frc2::SubsystemBase {
 public:
  Shooter();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();
  void setSpeed(double speed);
  double getSpeed();
 private:
  WPI_TalonSRX ShooterMaster {7};
  WPI_VictorSPX ShooterR1 {8}; 
  std::shared_ptr<nt::NetworkTable> visionTable = nt::NetworkTableInstance::GetDefault().GetTable("chameleon-vision");
  WPI_VictorSPX ShooterL1 {9};
  WPI_VictorSPX ShooterL2 {10};
  double kRPS = 0.0;
  double rps = 0.0;
  double pulsesPerRev = 4096/4;
  double targetWidth = 0;

};
