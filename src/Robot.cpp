
#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>

Robot::Robot() : TimedRobot()
{
}
void Robot::RobotInit()
{
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
void Robot::AutonomousInit(){
  container.autocommand = std::make_unique<frc2::SequentialCommandGroup>(
    container.chassis.getRamsetteCommand(
    frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)), 
    {
      frc::Translation2d(1.0_m,-1.0_m),
    },
    frc::Pose2d(2.0_m, -2.0_m, frc::Rotation2d(0_deg))
    ), 
  container.chassis.getRamsetteCommand(
    frc::Pose2d(2.0_m, -2.0_m, frc::Rotation2d(0_deg)), 
    {
      frc::Translation2d(1.0_m,-1.0_m),
    },
    frc::Pose2d(3.0_m, 0.0_m,frc::Rotation2d(180_deg)), true
    )
  );
  
  container.autocommand->Schedule();
}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit()
{

}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic(){

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

/*
 * 
 * <tipo> <nombre la funcion>(<parametros>){
 *  <cuerpo>
 * } 
 * 
 *  Rectangulo hola;
 *  
 * 
 * int area = hola.GetArea();
 * 
 * 
 * 
 * */
