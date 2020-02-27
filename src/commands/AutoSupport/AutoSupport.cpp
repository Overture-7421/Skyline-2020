/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "AutoSupport.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
AutoSupport::AutoSupport(Chassis* chassis, Shooter* shooter, Feeder* feeder) {
  // Add your commands here, e.g.
  AddCommands(
    frc2::InstantCommand(
            [feeder]() { 
               feeder->lowerFeeder(true); 
               feeder->feed(1.0); 

      }, feeder),
      chassis->getRamsetteCommand(
            frc::Pose2d(0_m,0_m,frc::Rotation2d(0_deg)),
            {},
            frc::Pose2d(3_m,0_m,frc::Rotation2d(0_deg)), false, 1.5
      ),
      frc2::InstantCommand(
                [feeder]() { 
                    feeder->lowerFeeder(false); 
                    feeder->feed(0.0); 

          }, feeder),
      chassis->getRamsetteCommand(
            frc::Pose2d(3_m,0_m,frc::Rotation2d(0_deg)),
            {},
            frc::Pose2d(0.5_m,3_m,frc::Rotation2d(160_deg)), true),
      Shoot(shooter, chassis, feeder, 5, 0.5)

  );
}
