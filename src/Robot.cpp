
#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>

Robot::Robot() : TimedRobot(){

}
void Robot::RobotInit(){
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
void Robot::RobotPeriodic() { 

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
void Robot::AutonomousInit() {


}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
    // angleController.EnableContinuousInput(-180.0, 180.0);
    // angleController.SetSetpoint(container.chassis.getYaw());
    // targetAngle = container.chassis.getYaw();
    // frc::SmartDashboard::PutNumber("Heading P", angleController.GetP());
    // frc::SmartDashboard::PutNumber("Heading I",  angleController.GetI());
    // frc::SmartDashboard::PutNumber("Heading D",  angleController.GetD());
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {
    // angleController.SetP(frc::SmartDashboard::GetNumber("Heading P",  angleController.GetP()));
    // angleController.SetI(frc::SmartDashboard::GetNumber("Heading I",  angleController.GetI()));
    // angleController.SetD(frc::SmartDashboard::GetNumber("Heading D",  angleController.GetD()));

    // frc::SmartDashboard::PutNumber("Heading Error", angleController.GetPositionError());
    // frc::SmartDashboard::PutNumber("Heading Target", targetAngle);

    // frc::SmartDashboard::PutNumber("Turn Command", control.GetX(frc::GenericHID::JoystickHand::kRightHand));
    // frc::SmartDashboard::PutNumber("Forward Command", control.GetY(frc::GenericHID::JoystickHand::kLeftHand));

    // targetAngle += control.GetX(frc::GenericHID::JoystickHand::kRightHand) * 0.005 * 90.0;

    // if(targetAngle > 180.0){
    //     targetAngle -= 360;
    // }

    // if(targetAngle < -180.0){
    //     targetAngle += 360;
    // }
    // angleController.SetSetpoint(targetAngle);
    // double angularSpeed = angleController.Calculate(container.chassis.getYaw());
    // container.chassis.arcadeDrive(control.GetY(frc::GenericHID::JoystickHand::kLeftHand), angularSpeed);

}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
