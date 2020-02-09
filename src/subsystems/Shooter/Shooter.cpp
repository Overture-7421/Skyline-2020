#include "Shooter.h"

Shooter::Shooter() {
    ShooterR1.Follow(ShooterMaster);

    ShooterL1.Follow(ShooterMaster);

    ShooterMaster.SetInverted(true);
    ShooterR1.SetInverted(true);

    ShooterMaster.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative); 
    ShooterMaster.ConfigClosedloopRamp(0.5);
    ShooterMaster.SetSelectedSensorPosition(0);

    ShooterMaster.Config_kP(0, 0.28000);
    ShooterMaster.Config_kI(0, 0.0);
    ShooterMaster.Config_kD(0, 10.0);
    ShooterMaster.Config_kF(0, 0.025000);

    //frc::SmartDashboard::PutNumber("Shooter/P", 0.25);
    //frc::SmartDashboard::PutNumber("Shooter/I", 0.0);
    //frc::SmartDashboard::PutNumber("Shooter/D", 0.5);
    //frc::SmartDashboard::PutNumber("Shooter/F", 0.025);
    frc::SmartDashboard::PutNumber("rps", 0.0);
}

void Shooter::setRPS(double rps){
    this->rps = rps;
}

bool Shooter::rpsObjectiveReached(){
    double currentVelocity = (ShooterMaster.GetSelectedSensorVelocity()/pulsesPerRev)*10;
    double error = -currentVelocity;


}



void Shooter::Periodic() {    

    //ShooterMaster.Config_kP(0, frc::SmartDashboard::GetNumber("Shooter/P", 0.25));
    //ShooterMaster.Config_kI(0, frc::SmartDashboard::GetNumber("Shooter/I", 0.0));
    //ShooterMaster.Config_kD(0, frc::SmartDashboard::GetNumber("Shooter/D", 0.5));
    //ShooterMaster.Config_kF(0, frc::SmartDashboard::GetNumber("Shooter/F", 0.025));

    frc::SmartDashboard::PutNumber("Shooter/velocity", (ShooterMaster.GetSelectedSensorVelocity()/pulsesPerRev)*10);
    frc::SmartDashboard::PutNumber("Shooter/Position", ShooterMaster.GetSelectedSensorPosition());

    rps = frc::SmartDashboard::GetNumber("rps", 0.0);
    double pulsesPerSecond = pulsesPerRev * rps;

    ShooterMaster.Set(ControlMode::Velocity,  pulsesPerSecond / 10.0); 
}
