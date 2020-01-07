/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"

RobotContainer::RobotContainer() : m_autonomousCommand(&m_subsystem) {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();
  chassis.SetDefaultCommand(frc2::RunCommand(
    [this] {
      chassis.Drive(
        xbox.GetY(frc::GenericHID::kLeftHand),
        xbox.GetY(frc::GenericHID::kRightHand)
      );
    },
  {&chassis}));
}

void RobotContainer::ConfigureButtonBindings() {
  
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autonomousCommand;
}
