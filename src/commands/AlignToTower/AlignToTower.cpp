/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "AlignToTower.h"

AlignToTower::AlignToTower(Chassis* chassis) {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(chassis);
  this->chassis = chassis;
}

// Called when the command is initially scheduled.
void AlignToTower::Initialize() {
  VisionController.Reset();
}

// Called repeatedly when this Command is scheduled to run
void AlignToTower::Execute() {
    visionYawInput = visionTable->GetNumber("Microsoft LifeCam HD-3000/targetYaw", 0);
    
    isValid = visionTable->GetBoolean("Microsoft LifeCam HD-3000/isValid", 0);
    VisionController.SetSetpoint(0);
    if(isValid){
      double visualangularSpeed = VisionController.Calculate(visionYawInput);
      chassis->arcadeDrive(0.0, visualangularSpeed);
    }else{
      chassis->arcadeDrive(0.0, 0.0);
    }
}

// Called once the command ends or is interrupted.
void AlignToTower::End(bool interrupted) {
  chassis->arcadeDrive(0.0, 0.0);
}

// Returns true when the command should end.
bool AlignToTower::IsFinished() {
  return std::abs(visionYawInput) < 1 && isValid ; 
}
