#include "Skyline.h"

Skyline::Skyline() : TimedRobot() {}

void Skyline::RobotInit() {}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Skyline::RobotPeriodic() { frc2::CommandScheduler::GetInstance().Run(); }

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Skyline::DisabledInit() {}

void Skyline::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Skyline::AutonomousInit() {}

void Skyline::AutonomousPeriodic() {}

void Skyline::TeleopInit() {}

/**
 * This function is called periodically during operator control.
 */
void Skyline::TeleopPeriodic() {}

/**
 * This function is called periodically during test mode.
 */
void Skyline::TestPeriodic() {}
