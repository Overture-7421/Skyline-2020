/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Shoot.h"

Shoot::Shoot(Shooter* shooter, Chassis* chassis, Feeder* feeder, int amount, double feedSpeed, double shootSpeed, bool useHood){
  this->shooter = shooter;
  this->chassis = chassis;
  this->feeder = feeder;
  this->ballsToShoot = amount;
  this->feedSpeed = feedSpeed;
  this->shootSpeed = shootSpeed;
  this->useHood = useHood;

  AddRequirements({shooter, chassis, feeder});
}

// Called when the command is initially scheduled.
void Shoot::Initialize() {
    frc::SmartDashboard::PutNumber("Vision P", VisionController.GetP());
    frc::SmartDashboard::PutNumber("Vision I", VisionController.GetI());
    frc::SmartDashboard::PutNumber("Vision D", VisionController.GetD());
    shooter->setRPS(20);
    shooter->feed(0);
    feeder->lowerFeeder(true);
    initialBalls = shooter->getBallsShot();
    visionLEDs.Set(false); 

}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute() {

  VisionController.SetP(frc::SmartDashboard::GetNumber("Vision P", VisionController.GetP()));
  VisionController.SetI(frc::SmartDashboard::GetNumber("Vision I", VisionController.GetI()));
  VisionController.SetD(frc::SmartDashboard::GetNumber("Vision D", VisionController.GetD()));

  VisionController.SetSetpoint(targetVision);
  bool isValid = visionTable->GetBoolean("VisionCamera/isValid", 0);
  double visionYawInput = visionTable->GetNumber("VisionCamera/targetYaw", 0);
  double targetPitch = visionTable->GetNumber("VisionCamera/targetPitch", 0);
  double distance = (h2 - h1) / tan( (targetPitch + a1) * M_PI / 180.0);
  frc::SmartDashboard::PutNumber("Vision/distance", distance);

  double targetRPS = 0;
  if(!useHood){
    targetRPS = 38;
    shooter->setHood(HoodPosition::CLOSE_RANGE);
  }else{
    targetRPS = 0.5 * distance + 45; 
    shooter->setHood(HoodPosition::LONG_RANGE);
  }

  double visualangularSpeed = VisionController.Calculate(visionYawInput);

  if (isValid) {
      chassis->arcadeDrive(0.0, visualangularSpeed);
  }else{
      chassis->arcadeDrive(0.0, 0);
  }

  if(std::abs(VisionController.GetPositionError()) <= 2.5) {
    //y = -371.06x + 52.406
      shooter->setRPS(shootSpeed);

      if(shooter->rpsObjectiveReached()){
        shooter->feed(feedSpeed);
      }
  }

}

// Called once the command ends or is interrupted.
void Shoot::End(bool interrupted) {
    shooter->setRPS(0);
    shooter->feed(0);
    feeder->lowerFeeder(false);
    visionLEDs.Set(true);
}

// Returns true when the command should end.
bool Shoot::IsFinished() {
  if(ballsToShoot == 0){
       return false; 
  } else {
    return shooter->getBallsShot() - initialBalls >= ballsToShoot;
  }
}
