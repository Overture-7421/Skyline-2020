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

  feedShooterButton.WhenPressed([this] { 
    shooter.feed(1.0);
    feeder.lowerFeeder(true);
   }).WhenReleased([this] { 
     shooter.feed(0.0); 
     feeder.lowerFeeder(false);
     });

  shootButton.WhenPressed([this] {
    Shoot(&shooter, &chassis);
  });
  //speedUpFlywheelButton.WhenPressed(SpeedUpShooter(&shooter, 100));
}