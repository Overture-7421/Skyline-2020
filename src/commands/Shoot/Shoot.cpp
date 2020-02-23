/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Shoot.h"

Shoot::Shoot(Shooter* shooter, Chassis* chassis){
  this->shooter = shooter;
  this->chassis = chassis;
}

// Called when the command is initially scheduled.
void Shoot::Initialize() {
    frc::SmartDashboard::PutNumber("Vision P", VisionController.GetP());
    frc::SmartDashboard::PutNumber("Vision I", VisionController.GetI());
    frc::SmartDashboard::PutNumber("Vision D", VisionController.GetD());
}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute() {
  bool isValid = visionTable->GetBoolean("VisionCamera/isValid", 0);

  VisionController.SetP(frc::SmartDashboard::GetNumber("Vision P", VisionController.GetP()));
  VisionController.SetI(frc::SmartDashboard::GetNumber("Vision I", VisionController.GetI()));
  VisionController.SetD(frc::SmartDashboard::GetNumber("Vision D", VisionController.GetD()));

  VisionController.SetSetpoint(targetVision);
  double visionYawInput = visionTable->GetNumber("VisionCamera/targetYaw", 0);
  double visualangularSpeed = VisionController.Calculate(visionYawInput);

  if (isValid) {
      chassis->arcadeDrive(0.0, visualangularSpeed);
  }
  
  if(std::abs(VisionController.GetPositionError()) <= 0.5) {
    frc::SmartDashboard::PutNumber("ShooterRPS", 40);
  }
}

// Called once the command ends or is interrupted.
void Shoot::End(bool interrupted) {}

// Returns true when the command should end.
bool Shoot::IsFinished() { return false; }
