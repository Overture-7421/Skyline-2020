/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Shoot.h"

Shoot::Shoot(Shooter* shooter, Chassis* chassis, Feeder* feeder, int amount){
  this->shooter = shooter;
  this->chassis = chassis;
  this->feeder = feeder;
  this->ballsToShoot = amount;

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
}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute() {

  VisionController.SetP(frc::SmartDashboard::GetNumber("Vision P", VisionController.GetP()));
  VisionController.SetI(frc::SmartDashboard::GetNumber("Vision I", VisionController.GetI()));
  VisionController.SetD(frc::SmartDashboard::GetNumber("Vision D", VisionController.GetD()));

  VisionController.SetSetpoint(targetVision);
  bool isValid = visionTable->GetBoolean("VisionCamera/isValid", 0);
  double visionYawInput = visionTable->GetNumber("VisionCamera/targetYaw", 0);
  double targetArea = visionTable->GetNumber("VisionCamera/targetArea", 0);


  if(targetArea <= 0.02 ){
    shooter->setHood(HoodPosition::LONG_RANGE);
  }else{
    shooter->setHood(HoodPosition::CLOSE_RANGE);
  }

  double visualangularSpeed = VisionController.Calculate(visionYawInput);

  if (isValid) {
      chassis->arcadeDrive(0.0, visualangularSpeed);
  }else{
      chassis->arcadeDrive(0.0, 0);
  }

  if(std::abs(VisionController.GetPositionError()) <= 3.5) {
    //y = -371.06x + 52.406
      shooter->setRPS(-371.06* targetArea + 52);

      if(shooter->rpsObjectiveReached()){
        shooter->feed(1);
      }
  }

}

// Called once the command ends or is interrupted.
void Shoot::End(bool interrupted) {
    shooter->setRPS(0);
    shooter->feed(0);
    feeder->lowerFeeder(false);
}

// Returns true when the command should end.
bool Shoot::IsFinished() {
  if(ballsToShoot == 0){
       return false; 
  } else {
    return shooter->getBallsShot() - initialBalls >= ballsToShoot;
  }
}
