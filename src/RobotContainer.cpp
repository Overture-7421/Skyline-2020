/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here
  // Configure the button bindings
  //autoPrelude = std::make_unique<frc2::SequentialCommandGroup>;
  chassis.SetDefaultCommand(TeleopDrive(&chassis, &driverControl));
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  feedIntakeButton.WhenPressed([this] { 
    feeder.feed(1.0);
    feeder.lowerFeeder(true);
   }).WhenReleased([this] { 
     feeder.feed(0.0); 
     feeder.lowerFeeder(false);
     });

  lowerIntakeButton.WhenPressed([this] { 
    feeder.lowerFeeder(true);
   }).WhenReleased([this] { 
     feeder.lowerFeeder(false);
     });

   shootButton.WhileHeld(Shoot(&shooter, &chassis, &feeder));
  //speedUpFlywheelButton.WhenPressed(SpeedUpShooter(&shooter, 100));
}