/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"

RobotContainer::RobotContainer() : ramseteCommand(chassis) {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  frc2::JoystickButton(&xbox,1).WhenHeld(ramseteCommand).WhenReleased(frc2::InstantCommand([this], {chassis.TankDrive(
    xbox.GetY(frc::XboxController::kLeftHand), xbox.GetY(frc::XboxController::kRightHand))
  )}); // A button

}

