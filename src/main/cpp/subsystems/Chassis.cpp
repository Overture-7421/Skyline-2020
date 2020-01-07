/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Chassis.h"

Chassis::Chassis() : leftmaster(ChassisMap::LEFT_MASTER), left1(ChassisMap::LEFT_1),
 left2(ChassisMap::LEFT_2), rightmaster(ChassisMap::RIGHT_MASTER), right1(ChassisMap::RIGHT_1),
 right2(ChassisMap::RIGHT_2) {
     leftmaster.ConfigOpenloopRamp(ChassisMap::RAMP);
     rightmaster.ConfigOpenloopRamp(ChassisMap::RAMP);
     leftmaster.SetNeutralMode(NeutralMode::Coast);
     rightmaster.SetNeutralMode(NeutralMode::Coast);
     right1.Follow(rightmaster);
     right2.Follow(rightmaster);
     left1.Follow(leftmaster);
     left2.Follow(leftmaster);
     std::cout << "Chassis Subsystem online" << std::endl;
 }

// This method will be called once per scheduler run
void Chassis::Periodic() {
    std::cout << "System works!" << std::endl;
}

void Chassis::Drive(float left, float right) {
    leftmaster.Set(ControlMode::PercentOutput, left);
    rightmaster.Set(ControlMode::PercentOutput, right);
}