#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <frc/Timer.h>
#include "Constants.h"
#include <frc/DoubleSolenoid.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/SlewRateLimiter.h>
#include <frc/DigitalInput.h>
#include <frc/Counter.h>
#include <frc/DigitalGlitchFilter.h>
#include <frc/Relay.h>
#include <units/units.h>
using namespace ctre::phoenix::motorcontrol::can;
using namespace ctre::phoenix::motorcontrol;

enum class HoodPosition
{
   CLOSE_RANGE,
   LONG_RANGE
};

class Shooter : public frc2::SubsystemBase
{
public:
   Shooter();
   void setRPS(double rps);
   bool rpsObjectiveReached();
   void feed(double output);
   void setHood(HoodPosition pos);
   int getBallsShot();
   double getCurrentRPS();
   /**
    * Will be called periodically whenever the CommandScheduler runs.
    */
   void Periodic() override;

private:
   frc::DigitalInput ballSwitch{9};
   frc::Counter ballCounter{&ballSwitch};
   frc::DigitalGlitchFilter ballSwitchFilter;
   frc::DoubleSolenoid hoodPiston{0, 1};
   frc::SlewRateLimiter<units::radians_per_second> rpsRateLimiter{units::radians_per_second_t(50) / units::second_t(1)};
   WPI_TalonSRX ShooterMaster{ShooterMap::MASTER_RIGHT};
   WPI_VictorSPX ShooterR1{ShooterMap::RIGHT_1};
   WPI_VictorSPX ShooterL1{ShooterMap::LEFT_1};

   WPI_VictorSPX ShooterFeeder{ShooterMap::FEEDER};
   WPI_VictorSPX StorageMotor{StorageMap::STORAGE_MOTOR};

   std::shared_ptr<nt::NetworkTable> visionTable = nt::NetworkTableInstance::GetDefault().GetTable("chameleon-vision");

   double radsPerSecond = 0.0;
   double pulsesPerRev = 4096;
   double targetWidth = 0;
   double tolerance = 5;
   const double timeToStableRPS = 1; //Seconds
   double lastTimeStable = frc::Timer::GetFPGATimestamp();
   bool lastOnTargetState = false;
};