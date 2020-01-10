#include "Chassis.h"

Chassis::Chassis() {
    frc::SmartDashboard::PutNumber("kP",0);
    frc::SmartDashboard::PutNumber("kI",0);
    frc::SmartDashboard::PutNumber("kD",0);
    frc::SmartDashboard::PutNumber("Target", 0);
    frc::SmartDashboard::PutNumber("Heading P", 0.01);
    leftEncoder.SetDistancePerPulse(0.000469043);
    rightEncoder.SetDistancePerPulse(0.000469043);
    rightMotor.ConfigOpenloopRamp(1/3);
    rightMotor1.ConfigOpenloopRamp(1/3);
    leftMotor.ConfigOpenloopRamp(1/3);
    leftMotor1.ConfigOpenloopRamp(1/3);
    /**
     * Trajectory code commented out to test correct command offloading 
     * */
    //  frc::TrajectoryConfig config(units::meters_per_second_t(2),
    //                           units::meters_per_second_squared_t(2));
    // targetTrajectory = frc::TrajectoryGenerator::GenerateTrajectory(
    //   // Start at the origin facing the +X direction
    //   frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
    //   // Pass through these two interior waypoints, making an 's' curve path
    //   {frc::Translation2d(1_m, 1_m), frc::Translation2d(2_m, -1_m)},
    //   // End 3 meters straight ahead of where we started, facing forward
    //   frc::Pose2d(3_m, 0_m, frc::Rotation2d(0_deg)),
    //   // Pass the config
    //   config
    //   );
}

void Chassis::Periodic(){
    
    frc::SmartDashboard::PutNumber("Error left", leftPID.GetPositionError());
    frc::SmartDashboard::PutNumber("Error right", rightPID.GetPositionError());
    // leftPID.SetP(frc::SmartDashboard::GetNumber("kP",0));
    // leftPID.SetI(frc::SmartDashboard::GetNumber("kI",0));
    // leftPID.SetD(frc::SmartDashboard::GetNumber("kD",0));
    // rightPID.SetP(frc::SmartDashboard::GetNumber("kP",0));
    // rightPID.SetI(frc::SmartDashboard::GetNumber("kI",0));
    // rightPID.SetD(frc::SmartDashboard::GetNumber("kD",0));
    

    // differentialDrive.TankDrive(leftPID.Calculate(leftEncoder.GetRate()) , rightPID.Calculate(rightEncoder.GetRate()));
   
     frc::Rotation2d gyroAngle{units::degree_t(-gyro.GetAngle())};
     pose = odometry.Update(gyroAngle, units::meter_t(leftEncoder.GetDistance()),
     units::meter_t(rightEncoder.GetDistance()));

    //  ChassisSpeeds speeds = ramsete.Calculate(pose, targetTrajectory.Sample(2_s));
    //  DifferentialDriveWheelSpeeds wheelsSpeed = kinematis.ToWheelSpeeds(speeds);
    // leftPID.SetSetpoint(double_t(wheelsSpeed.left));
    // rightPID.SetSetpoint(double_t(wheelsSpeed.right));

}

void Chassis::drive(double linear, double angular){
    this->linear = linear;
    this->angular = angular;
}

double Chassis::getYaw(){
    return gyro.GetYaw();
}

void Chassis::UpdateBoard() {
    frc::SmartDashboard::PutNumber("X", double_t(odometry.GetPose().Translation().X()));
    frc::SmartDashboard::PutNumber("Right Encoder", rightEncoder.GetRate());
    frc::SmartDashboard::PutNumber("Left encoder", leftEncoder.GetRate());
    frc::SmartDashboard::PutNumber("Y", double_t(odometry.GetPose().Translation().Y()));
    frc::SmartDashboard::PutNumber("Heading", gyro.GetYaw());
    frc::SmartDashboard::PutNumber("Left Encoder",leftEncoder.Get());
    frc::SmartDashboard::PutNumber("Right Encoder", rightEncoder.Get());
}

void Chassis::Ramsete(frc::Trajectory target) {
    
   differentialDrive.TankDrive(leftPID.Calculate(leftEncoder.GetRate()) , rightPID.Calculate(rightEncoder.GetRate()));
    frc::Rotation2d gyroAngle{units::degree_t(-gyro.GetAngle())};
    // pose = odometry.Update(gyroAngle, units::meter_t(leftEncoder.GetDistance()),
    //  units::meter_t(rightEncoder.GetDistance()));

     ChassisSpeeds speeds = ramsete.Calculate(pose, targetTrajectory.Sample(2_s));
     DifferentialDriveWheelSpeeds wheelsSpeed = kinematis.ToWheelSpeeds(speeds);
    leftPID.SetSetpoint(double_t(wheelsSpeed.left));
    rightPID.SetSetpoint(double_t(wheelsSpeed.right));
}

void Chassis::TankDrive(double l, double r) {
    this->differentialDrive.TankDrive(l,r);
}
