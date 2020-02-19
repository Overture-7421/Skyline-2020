#include "Shooter.h"

Shooter::Shooter() {
    ShooterR1.Follow(ShooterMaster);
    ShooterL2.Follow(ShooterMaster);

    ShooterMaster.SetInverted(true);
    ShooterR1.SetInverted(true);

    ShooterMaster.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative); 
    ShooterMaster.ConfigClosedloopRamp(0.1);
    ShooterMaster.SetSelectedSensorPosition(0);

    ShooterMaster.Config_kP(0, 0.28000);
    ShooterMaster.Config_kI(0, 0.0);
    ShooterMaster.Config_kD(0, 10.0);
    ShooterMaster.Config_kF(0, 0.025000);
    frc::SmartDashboard::PutNumber("Shooter/rps",0);

}

void Shooter::setRPS(double rps){
    this->rps = rps;
}


bool Shooter::rpsObjectiveReached(){
    double currentVelocity = (ShooterMaster.GetSelectedSensorVelocity()/pulsesPerRev)*10;
    double error = rps - currentVelocity;
    double currentTime = frc::Timer::GetFPGATimestamp();
    bool onTarget = abs(error) < tolerance;

    bool onTargetChanged = onTarget != lastOnTargetState;

    if(onTarget && onTargetChanged){
        lastTimeStable = currentTime;
    }

    lastOnTargetState = onTarget;
    return currentTime - lastTimeStable > timeToStableRPS && onTarget;
}

void Shooter::Periodic() {    
    frc::SmartDashboard::PutNumber("Shooter/velocity", (ShooterMaster.GetSelectedSensorVelocity()/pulsesPerRev)*10);
    frc::SmartDashboard::PutNumber("Shooter/Position", ShooterMaster.GetSelectedSensorPosition());
    frc::SmartDashboard::PutBoolean("Shooter/Objective Reached", rpsObjectiveReached());
    targetWidth = visionTable->GetNumber("Microsoft LifeCam HD-3000/targetBoundingWidth", 0);

    rps = frc::SmartDashboard::GetNumber("Shooter/rps",0);
    
    double pulsesPerSecond = pulsesPerRev * rps;

    ShooterMaster.Set(ControlMode::Velocity,  pulsesPerSecond / 10.0); 
}
