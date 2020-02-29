#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>

Robot::Robot() : TimedRobot()
{
}
void Robot::RobotInit()
{
    container.chassis.setRateLimit(false);
    std::cout << "Robot is online" << std::endl;
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic()
{

  frc2::CommandScheduler::GetInstance().Run();
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit()
{
  // container.autocommand = std::make_unique<frc2::SequentialCommandGroup>(
  //    container.chassis.getRamsetteCommand(
  //    frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
  //   {
  //     frc::Translation2d(1.0_m,-1.0_m),
  //   },
  //   frc::Pose2d(2.0_m, -2.0_m, frc::Rotation2d(0_deg))
  //   ),
  // container.chassis.getRamsetteCommand(
  //   frc::Pose2d(2.0_m, -2.0_m, frc::Rotation2d(0_deg)),
  //   {
  //     frc::Translation2d(1.0_m,-1.0_m),
  //   },
  //   frc::Pose2d(3.0_m, 0.0_m,frc::Rotation2d(180_deg)), true
  //   )
  // );
  container.autoChooser.GetSelected()->Schedule();
  // container.autocommand->Schedule();
}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit()
{
    container.chassis.setRateLimit(true);
    //container.climb.climb();
    // frc::SmartDashboard::PutBoolean("ShooterHood", false);
    // frc::SmartDashboard::PutNumber("ShooterRPS", 0);
    // frc::SmartDashboard::PutNumber("ShooterFeed", 0);
    // frc::SmartDashboard::PutNumber("FeederOutput", 0);
    frc::SmartDashboard::PutNumber("climbVelocity", 0);
    frc::SmartDashboard::PutNumber("winchVelocity", 0);
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic()
{
  if(abs(container.operatorControl.GetY(frc::GenericHID::JoystickHand::kLeftHand)) > 0.15)
  {
    container.climb.climb(-container.operatorControl.GetY(frc::GenericHID::JoystickHand::kLeftHand));
  }
  else{
    container.climb.climb(0);
  }

  if(abs(container.operatorControl.GetY(frc::GenericHID::JoystickHand::kRightHand)) > 0.15){
    container.climb.winch(-container.operatorControl.GetY(frc::GenericHID::JoystickHand::kRightHand));
  }
  else{
    container.climb.winch(0);


  }

    // double targetPitch = visionTable->GetNumber("VisionCamera/targetPitch", 0);
    // double distance = (h2 - h1) / tan( (targetPitch + a1) * M_PI / 180.0);
    // frc::SmartDashboard::PutNumber("distance", distance);

    // container.shooter.setHood(frc::SmartDashboard::GetBoolean("ShooterHood", false) ? HoodPosition::LONG_RANGE : HoodPosition::CLOSE_RANGE);
    //container.shooter.setRPS(frc::SmartDashboard::GetNumber("ShooterRPS", 0));
    // container.shooter.feed(frc::SmartDashboard::GetNumber("ShooterFeed", 0));
    // container.feeder.feed(frc::SmartDashboard::GetNumber("FeederOutput", 0));
    // container.climb.climb(frc::SmartDashboard::GetNumber("climbVelocity", 0));
    // container.climb.winch(frc::SmartDashboard::GetNumber("winchVelocity", 0));
  }

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif