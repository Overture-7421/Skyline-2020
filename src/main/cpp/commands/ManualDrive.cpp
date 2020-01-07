/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ManualDrive.h"
ManualDrive::ManualDrive(Chassis* chassis) {
 AddRequirements(chassis);
}

// Called when the command is initially scheduled.
void ManualDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ManualDrive::Execute() {}

// Called once the command ends or is interrupted.
void ManualDrive::End(bool interrupted) {}

// Returns true when the command should end.
bool ManualDrive::IsFinished() { return false; }
