/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "commands/Shoot/Shoot.h"
#include "subsystems/Shooter/Shooter.h"
#include "subsystems/Chassis/Chassis.h"
#include "commands/AlignToTower/AlignToTower.h"
#include "subsystems/Feeder/Feeder.h"

class AutoSupport
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 AutoSupport> {
 public:
  AutoSupport(Chassis* chassis, Shooter* shooter, Feeder* feeder);
};
