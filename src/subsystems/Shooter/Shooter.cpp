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

    frc::SmartDashboard::PutNumber("Shooter P", 0.1);
    frc::SmartDashboard::PutNumber("Shooter I", 0.0);
    frc::SmartDashboard::PutNumber("Shooter D", 0.0);
    frc::SmartDashboard::PutNumber("Shooter F", 0.03);

    frc::SmartDashboard::PutNumber("rps", 0.0);
    

}

// This method will be called once per scheduler run
void Shooter::Periodic() {    
    double pulsesPerRev = 4096/4;

    ShooterMaster.Config_kP(0,frc::SmartDashboard::GetNumber("Shooter P", 0.0));
    ShooterMaster.Config_kI(0,frc::SmartDashboard::GetNumber("Shooter I", 0.0));
    ShooterMaster.Config_kD(0,frc::SmartDashboard::GetNumber("Shooter D", 0.0));
    ShooterMaster.Config_kF(0,frc::SmartDashboard::GetNumber("Shooter F", 0.0));
    frc::SmartDashboard::PutNumber("velocity", (ShooterMaster.GetSelectedSensorVelocity()/pulsesPerRev)*10);
    frc::SmartDashboard::PutNumber("Position", ShooterMaster.GetSelectedSensorPosition());

    double rps = frc::SmartDashboard::GetNumber("rps", 0.0);

    double pulsesPerSecond = pulsesPerRev * rps;

    ShooterMaster.Set(ControlMode::Velocity,  pulsesPerSecond / 10.0); 
}
