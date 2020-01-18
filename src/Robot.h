/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <iostream>
#include "RobotContainer.h"
#include <frc/XboxController.h>
#include <frc/drive/DifferentialDrive.h>

class Robot : public frc::TimedRobot {
 public:
  Robot();
  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

	frc::XboxController controller {0};

 private:
  frc2::Command* autoCommand;
   RobotContainer container;
  
  // frc2::PIDController angleController {0,0,0, units::second_t(5_ms)};
  // double targetAngle = 0.0;
};
