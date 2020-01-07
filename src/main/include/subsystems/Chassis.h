/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "Constants.h"
#include <iostream>
#include <frc2/command/SubsystemBase.h>
#include "ctre/Phoenix.h"
class Chassis : public frc2::SubsystemBase {
 public:
  Chassis();
  void Drive(float left, float right);
  void Periodic();

 private:
    VictorSPX leftmaster;
    VictorSPX rightmaster;
    VictorSPX right1;
    VictorSPX right2;
    VictorSPX left1;
    VictorSPX left2;
};
