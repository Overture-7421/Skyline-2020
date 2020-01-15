
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
void Robot::AutonomousInit()
{
  
}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit()
{

}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic(){
  double linear = controller.GetY(XboxController::JoystickHand::kLeftHand);
  double angular = -controller.GetX(XboxController::JoystickHand::kRightHand);


  rightMotor.Set(linear-angular);
  rightMotor1.Set(linear-angular);
  rightMotor2.Set(linear-angular);
  
  leftMotor.Set(-(linear+angular));
  leftMotor1.Set(-(linear+angular));
  leftMotor2.Set(-(linear+angular));
  
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
