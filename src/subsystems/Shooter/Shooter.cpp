#include "Shooter.h"

Shooter::Shooter() {
    ShooterR1.Follow(ShooterMaster);
    ShooterL1.Follow(ShooterMaster);
    ShooterL2.Follow(ShooterMaster);

    ShooterL1.SetInverted(InvertType::FollowMaster);
    ShooterL2.SetInverted(InvertType::FollowMaster);

    ShooterMaster.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative); 
    ShooterMaster.SetSensorPhase(true);
    
    ShooterMaster.SetSelectedSensorPosition(0);
    frc::SmartDashboard::PutNumber("kP-RPS",0.0);
    frc::SmartDashboard::PutNumber("Shooter P", 0.1);
    frc::SmartDashboard::PutNumber("Shooter I", 0.0);
    frc::SmartDashboard::PutNumber("Shooter D", 0.0);
    frc::SmartDashboard::PutNumber("Shooter F", 0.03);

    frc::SmartDashboard::PutNumber("rps", 0.0);
    

}

// This method will be called once per scheduler run
void Shooter::Periodic() {    
    ShooterMaster.Config_kP(0,frc::SmartDashboard::GetNumber("Shooter P", 0.0));
    ShooterMaster.Config_kI(0,frc::SmartDashboard::GetNumber("Shooter I", 0.0));
    ShooterMaster.Config_kD(0,frc::SmartDashboard::GetNumber("Shooter D", 0.0));
    ShooterMaster.Config_kF(0,frc::SmartDashboard::GetNumber("Shooter F", 0.0));
    frc::SmartDashboard::PutNumber("velocity", (ShooterMaster.GetSelectedSensorVelocity()/pulsesPerRev)*10);
    frc::SmartDashboard::PutNumber("Position", ShooterMaster.GetSelectedSensorPosition());
    targetWidth = visionTable->GetNumber("Microsoft LifeCam HD-3000/targetBoundingWidth", 0);
    kRPS = frc::SmartDashboard::GetNumber("kP-RPS",0.0);

   // double rps = frc::SmartDashboard::GetNumber("rps", 0.0);

    
    rps = targetWidth * kRPS;
    double pulsesPerSecond = pulsesPerRev * rps;
    ShooterMaster.Set(ControlMode::Velocity,  pulsesPerSecond / 10.0); 
}

void Shooter::setSpeed(double speed) {
    ShooterMaster.Set(ControlMode::Velocity, (speed * pulsesPerRev) /10.0);
    frc::SmartDashboard::PutNumber("rps", speed);
}

