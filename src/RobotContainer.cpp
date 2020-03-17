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


  autoChooser.SetDefaultOption("AutoPrelude",std::make_unique<AutoPrelude>(&chassis , &shooter, &feeder));
  autoChooser.AddOption("AutoSupport", std::make_unique<AutoSupport>(&chassis , &shooter, &feeder));
  frc::SmartDashboard::PutData("AutoChooser", &autoChooser);
}

void RobotContainer::ConfigureButtonBindings() {
  feedShooterButton.WhenPressed([this] {
    shooter.feed(0.7);
  }).WhenReleased([this] {
    shooter.feed(0.0);
  });
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

  panicButton.WhenPressed([this] {
    shooter.feed(-0.5);
    shooter.setRPS(-10);
  }).WhenReleased([this] {
    shooter.feed(0.0);
    shooter.setRPS(0.0);
  });

  reverseFeeder.WhenPressed([this] {
    feeder.feed(-1.0);
    feeder.lowerFeeder(true);
  }).WhenReleased([this] {
    feeder.feed(0.0);
    feeder.lowerFeeder(false);
  });

   shootCloseButton.WhileHeld(Shoot(&shooter, &chassis, &feeder, 0, 0.7, 35));
   shootFarButton.WhileHeld(Shoot(&shooter, &chassis, &feeder, 0, 0.7, 45, true));
  //speedUpFlywheelButton.WhenPressed(SpeedUpShooter(&shooter, 100));
}