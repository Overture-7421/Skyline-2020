/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "AutoPrelude.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
AutoPrelude::AutoPrelude(Chassis* chassis, Shooter* shooter, Feeder* feeder) {
  // Add your commands here, e.g.
  
   AddCommands(
      chassis->getRamsetteCommand(
         frc::Pose2d(0_m,0_m,frc::Rotation2d(0_deg)),
         {/*Empty vec*/},
         frc::Pose2d(1.7_m, -0.20_m,frc::Rotation2d(-90_deg))),
      Shoot(shooter, chassis, feeder, 3, 0.7, 45, true),
      frc2::InstantCommand(
      [shooter]() {
            shooter->setRPS(0.0);

      }, shooter),
      frc2::InstantCommand(
            [feeder]() { 
               feeder->lowerFeeder(true); 
               feeder->feed(1.0); 

      }, feeder),
       chassis->getRamsetteCommand(
         frc::Pose2d(1.7_m, -0.20_m,frc::Rotation2d(-90_deg)),
         {},
         frc::Pose2d(0.4_m,1.0_m,frc::Rotation2d(90_deg)), false),
      chassis->getRamsetteCommand(
         frc::Pose2d(0.4_m,1.5_m, frc::Rotation2d(90_deg)),
         {},
         frc::Pose2d(0.18_m,5.3_m,frc::Rotation2d(90_deg)), false, 1.5),
      frc2::InstantCommand(
            [feeder]() { 
               feeder->lowerFeeder(false); 
               feeder->feed(0.0); 

      }, feeder),
      chassis->getRamsetteCommand(
         frc::Pose2d(0.35_m,5.5_m,frc::Rotation2d(90_deg)),
         {/*Empty vec*/},
         frc::Pose2d(1.7_m, 0.5_m,frc::Rotation2d(-90_deg)),true),
       Shoot(shooter, chassis, feeder, 3, 0.7, 45, true)
   );
}
