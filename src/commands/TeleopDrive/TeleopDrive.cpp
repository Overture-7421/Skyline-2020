#include "TeleopDrive.h"

TeleopDrive::TeleopDrive(Chassis* chassis, frc::XboxController* xbox) : control(xbox) {
    AddRequirements(chassis);
    this->chassis = chassis;
    angleController.EnableContinuousInput(-180.0, 180.0);
    SetName("TeleopDrive");
    
}

void TeleopDrive::Initialize(){
    angleController.SetSetpoint(-chassis->getYaw());
    targetAngle = -chassis->getYaw();
    frc::SmartDashboard::PutNumber("Heading P", angleController.GetP());
    frc::SmartDashboard::PutNumber("Heading I",  angleController.GetI());
    frc::SmartDashboard::PutNumber("Heading D",  angleController.GetD());

    frc::SmartDashboard::PutNumber("Vision P", VisionController.GetP());
    frc::SmartDashboard::PutNumber("Vision I", VisionController.GetI());
    frc::SmartDashboard::PutNumber("Vision D", VisionController.GetD());
    

void TeleopDrive::Execute() {
    double visionYaw = visionTable->GetNumber("Microsoft LifeCam HD-3000/targetYaw", 0);
    bool isValid = visionTable->GetBoolean("Microsoft LifeCam HD-3000/isValid", 0);

    angleController.SetP(frc::SmartDashboard::GetNumber("Heading P",  angleController.GetP()));
    angleController.SetI(frc::SmartDashboard::GetNumber("Heading I",  angleController.GetI()));
    angleController.SetD(frc::SmartDashboard::GetNumber("Heading D",  angleController.GetD()));

    frc::SmartDashboard::PutNumber("Heading Error", angleController.GetPositionError());
    frc::SmartDashboard::PutNumber("Heading Target", targetAngle);
    frc::SmartDashboard::PutNumber("Turn Command", control->GetX(frc::GenericHID::JoystickHand::kRightHand));
    frc::SmartDashboard::PutNumber("Forward Command", control->GetY(frc::GenericHID::JoystickHand::kLeftHand));

    targetAngle += -control->GetX(frc::GenericHID::JoystickHand::kRightHand) * 0.02 * 270;
    if(targetAngle > 180.0){
        targetAngle -= 360;
    }

    if(targetAngle < -180.0){
        targetAngle += 360;
    }


    VisionController.SetP(frc::SmartDashboard::GetNumber("Vision P", VisionController.GetP()));
    VisionController.SetI(frc::SmartDashboard::GetNumber("Vision I", VisionController.GetI()));
    VisionController.SetD(frc::SmartDashboard::GetNumber("Vision D", VisionController.GetD()));

    
    VisionController.SetSetpoint(targetVision);
    double visualangularSpeed = VisionController.Calculate(visionYaw);


    angleController.SetSetpoint(targetAngle);
    double angularSpeed = angleController.Calculate(-chassis->getYaw());
    
    if (isValid && control->GetBumper(frc::GenericHID::JoystickHand::kRightHand)){
        chassis->arcadeDrive(-control->GetY(frc::GenericHID::JoystickHand::kLeftHand), visualangularSpeed);
        targetAngle = -chassis->getYaw();
    }else{
        chassis->arcadeDrive(-control->GetY(frc::GenericHID::JoystickHand::kLeftHand), angularSpeed);
    }
}


void TeleopDrive::End(bool interrupted){

}

bool TeleopDrive::IsFinished(){
    return false;
}
