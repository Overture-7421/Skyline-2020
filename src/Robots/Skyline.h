/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2021 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include "Core/MotorHandler/EctoMotor/EctoGazeboMotor.h"
#include "Core/PCM/EctoPiston/EctoGazeboPiston.h"

class Skyline : public frc::TimedRobot {
public:
    Skyline();

    void RobotInit() override;

    void RobotPeriodic() override;

    void DisabledInit() override;

    void DisabledPeriodic() override;

    void AutonomousInit() override;

    void AutonomousPeriodic() override;

    void TeleopInit() override;

    void TeleopPeriodic() override;

    void TestPeriodic() override;

private:
    const double deadband = 0.15;

    frc::Joystick xboxController{0};
    EctoGazeboMotor leftMotor{"TankChassis", "LeftChassis"};
    EctoGazeboMotor rightMotor{"TankChassis", "RightChassis"};
};
