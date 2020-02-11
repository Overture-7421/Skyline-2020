#include "SpeedUpShooter.h"

SpeedUpShooter::SpeedUpShooter(Shooter* shooter, double targetRPS){
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(shooter);
  this->shooter = shooter;
  this->targetRPS = targetRPS;
}

// Called when the command is initially scheduled.
void SpeedUpShooter::Initialize(){
  shooter->setRPS(targetRPS);
}

// Called repeatedly when this Command is scheduled to run
void SpeedUpShooter::Execute() {}


// Called once the command ends or is interrupted.
void SpeedUpShooter::End(bool interrupted) {}

// Returns true when the command should end.
bool SpeedUpShooter::IsFinished() { 
  
  return shooter->rpsObjectiveReached(); 
  
  }
