#include "Shooter.h"

Shooter::Shooter()
{
    ShooterMaster.ConfigFactoryDefault();

    ShooterFeeder.ConfigOpenloopRamp(0.2);
    ShooterFeeder.SetInverted(true);
    StorageMotor.ConfigOpenloopRamp(0.2);
    StorageMotor.Follow(ShooterFeeder);

    ballSwitchFilter.SetPeriodNanoSeconds(1250000);
    ballSwitchFilter.Add(&ballCounter);

    ShooterMaster.ConfigContinuousCurrentLimit(30);
    ShooterR1.Follow(ShooterMaster);
    ShooterL1.Follow(ShooterMaster);

    ShooterL1.SetInverted(true);

    ShooterMaster.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
    ShooterMaster.SetSelectedSensorPosition(0);
    ShooterMaster.ConfigSelectedFeedbackCoefficient(1);

    ShooterMaster.Config_kP(0, 0.28000);
    ShooterMaster.Config_kI(0, 0.0);
    ShooterMaster.Config_kD(0, 10.0);
    ShooterMaster.Config_kF(0, 0.025000);
}

void Shooter::setRPS(double rps)
{
    this->radsPerSecond = rps;
}

bool Shooter::rpsObjectiveReached()
{
    double currentVelocity = getCurrentRPS();
    double error = radsPerSecond - currentVelocity;
    double currentTime = frc::Timer::GetFPGATimestamp();
    bool onTarget = abs(error) < tolerance;

    bool onTargetChanged = onTarget != lastOnTargetState;

    if (onTarget && onTargetChanged)
    {
        lastTimeStable = currentTime;
    }

    lastOnTargetState = onTarget;
    return currentTime - lastTimeStable > timeToStableRPS && onTarget;
}

void Shooter::feed(double output)
{
    if (rpsObjectiveReached() && radsPerSecond > 10)
    {
        ShooterFeeder.Set(output);
    }
    else
    {
        ShooterFeeder.Set(0.0);
    }
}

void Shooter::setHood(HoodPosition pos)
{
    switch (pos)
    {
    case HoodPosition::CLOSE_RANGE:
        hoodPiston.Set(frc::DoubleSolenoid::kForward);
        break;
    case HoodPosition::LONG_RANGE:
        hoodPiston.Set(frc::DoubleSolenoid::kReverse);
        break;
    default:
        break;
    }
}

int Shooter::getBallsShot()
{
    return ballCounter.Get();
}

double Shooter::getCurrentRPS()
{
    return (ShooterMaster.GetSelectedSensorVelocity() / pulsesPerRev) * M_2_PI * 10;
}

void Shooter::Periodic()
{
    frc::SmartDashboard::PutNumber("Shooter/Velocity", getCurrentRPS());
    frc::SmartDashboard::PutNumber("Shooter/Position", ShooterMaster.GetSelectedSensorPosition());
    frc::SmartDashboard::PutBoolean("Shooter/ObjectiveReached", rpsObjectiveReached());
    frc::SmartDashboard::PutNumber("Shooter/BallsCounted", getBallsShot());

    //targetWidth = visionTable->GetNumber("Microsoft LifeCam HD-3000/TargetBoundingWidth", 0);
    double targetRPS = rpsRateLimiter.Calculate(units::radians_per_second_t(radsPerSecond)).to<double>();
    frc::SmartDashboard::PutNumber("Shooter/RateLimitedRPS", targetRPS);
    double pulsesPerSecond = pulsesPerRev * targetRPS / M_2_PI;
    ShooterMaster.Set(ControlMode::Velocity, pulsesPerSecond / 10.0);
}
