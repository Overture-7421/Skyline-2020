/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RamseteExample.h"

RamseteExample::RamseteExample(Chassis* chassis) {
  this->chassis = chassis;
  SetName("RamseteExample");
  // Use addRequirements() here to declare subsystem dependencies.
  this->AddRequirements({chassis});
}

// Called when the command is initially scheduled.
void RamseteExample::Initialize() {
  this->targetTrajectory = frc::TrajectoryGenerator::GenerateTrajectory(
      // Start at the origin facing the +X direction
      frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
      // Pass through these two interior waypoints, making an 's' curve path
      {frc::Translation2d(1_m, 1_m), frc::Translation2d(2_m, -1_m)},
      // End 3 meters straight ahead of where we started, facing forward
      frc::Pose2d(3_m, 0_m, frc::Rotation2d(0_deg)),
      // Pass the config
      this->config
      );
}

// Called repeatedly when this Command is scheduled to run
void RamseteExample::Execute() {
  this->chassis->Ramsete(this->targetTrajectory);
}
// Called once the command ends or is interrupted.
void RamseteExample::End(bool interrupted) {
  std::cout << "Ramsete command interrupted" << std::endl;
  this->chassis->TankDrive(0,0);
}

// Returns true when the command should end.
bool RamseteExample::IsFinished() { 
    return false;
  }
