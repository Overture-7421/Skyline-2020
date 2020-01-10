/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/StraightDrive.h"

StraightDrive::StraightDrive() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void StraightDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void StraightDrive::Execute() {}

// Called once the command ends or is interrupted.
void StraightDrive::End(bool interrupted) {}

// Returns true when the command should end.
bool StraightDrive::IsFinished() { return false; }
