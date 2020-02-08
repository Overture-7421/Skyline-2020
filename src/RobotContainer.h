
#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/button/Trigger.h>
#include "subsystems/Chassis.h"
#include "frc2/command/RunCommand.h"
#include "frc/XboxController.h"
#include "commands/TeleopDrive/TeleopDrive.h"
#include "subsystems/Shooter/Shooter.h"
#include "commands/AutoPrelude/AutoPrelude.h"

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
  std::unique_ptr<frc2::Command> TeleopDrive;
  Chassis chassis;
  Shooter shooter;
 AutoPrelude autoprelude{&chassis};
 private:
  // The robot's subsystems and commands are defined here...
  frc::XboxController xbox{0};
  
  void ConfigureButtonBindings();
};
