
#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/button/Trigger.h>
#include "subsystems/Chassis/Chassis.h"
#include "subsystems/Shooter/Shooter.h"
#include "subsystems/Feeder/Feeder.h"
#include "frc2/command/RunCommand.h"
#include "frc/XboxController.h"
#include "commands/TeleopDrive/TeleopDrive.h"
#include "commands/AutoPrelude/AutoPrelude.h"
#include "commands/SpeedUpShooter/SpeedUpShooter.h"
#include "commands/Shoot/Shoot.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */

class RobotContainer {
public:
  RobotContainer();
  std::unique_ptr<frc2::SequentialCommandGroup> autocommand;

  Chassis chassis;
  Shooter shooter;
  Feeder feeder;

  // The robot's subsystems and commands are defined here...
  frc::XboxController driverControl{0};
  frc::XboxController operatorControl{1};

private:
  frc2::Button speedUpFlywheelButton{[&] { return operatorControl.GetAButton(); }};
  frc2::Button feedIntakeButton{[&] { return operatorControl.GetBButton(); }};
  frc2::Button feedShooterButton{[&] { return operatorControl.GetYButton(); }};
  frc2::Button shootButton{[&] {return operatorControl.GetXButton(); }};

  void ConfigureButtonBindings();
};