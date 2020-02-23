/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "subsystems/Shooter/Shooter.h"
#include "subsystems/Chassis/Chassis.h"
#include "subsystems/Feeder/Feeder.h"
#include <frc/controller/PIDController.h>
#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTable.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class Shoot
    : public frc2::CommandHelper<frc2::CommandBase, Shoot>
{
public:
  Shoot(Shooter* shooter, Chassis* chassis, Feeder* feeder, int amount = 0);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  Shooter *shooter;
  Chassis *chassis;
  Feeder* feeder;
  double targetAngle = 0.0;
  int ballsToShoot = 0;
  int initialBalls = 0;

  std::shared_ptr<nt::NetworkTable> visionTable = nt::NetworkTableInstance::GetDefault().GetTable("chameleon-vision");
  frc2::PIDController VisionController{0.055, 0.050, 0.005};
  double targetVision = 0.0;
};
