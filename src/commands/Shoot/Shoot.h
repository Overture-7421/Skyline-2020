/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "subsystems/Shooter/Shooter.h"
#include "subsystems/Chassis/Chassis.h"
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
  Shoot();

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  bool isValid = false;
  Chassis *chassis;
  Shooter *Shooter;

  frc2::PIDController angleController{0.013, 0, 0.002};
  double targetAngle = 0.0;

  std::shared_ptr<nt::NetworkTable> visionTable = nt::NetworkTableInstance::GetDefault().GetTable("chameleon-vision");

  frc2::PIDController VisionController{0.015, 0.00002, 0.003};
  double targetVision = 0.0;





};
