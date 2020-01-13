#include "Chassis.h"
#include "commands/TeleopDrive/TeleopDrive.h"

Chassis::Chassis() {
    gyro.Reset();
    gyro.ZeroYaw();
    gyro.ResetDisplacement();
    frc::SmartDashboard::PutData("Chassis/Chassis",this);
    leftMaster.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
    rightMaster.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);

    leftMaster.ConfigSelectedFeedbackCoefficient(ChassisMap::ENC_METER_PER_PULSE);
    rightMaster.ConfigSelectedFeedbackCoefficient(ChassisMap::ENC_METER_PER_PULSE);

    rightMotor1.Follow(rightMaster);
    rightMotor2.Follow(rightMaster);

    leftMotor1.Follow(leftMaster);
    leftMotor2.Follow(leftMaster);

    leftMaster.ConfigOpenloopRamp(ChassisMap::RAMP_RATE);
    rightMaster.ConfigOpenloopRamp(ChassisMap::RAMP_RATE);
}

void Chassis::Periodic() {
    frc::SmartDashboard::PutNumber("Chassis/X", double_t(odometry.GetPose().Translation().X()));
    frc::SmartDashboard::PutNumber("Chassis/Y", double_t(odometry.GetPose().Translation().Y()));
    frc::SmartDashboard::PutNumber("Chassis/yaw", gyro.GetYaw());
    frc::SmartDashboard::PutNumber("Chassis/pitch", gyro.GetPitch());
    frc::SmartDashboard::PutNumber("Chassis/roll", gyro.GetRoll());
    frc::SmartDashboard::PutNumber("Chassis/heading", gyro.GetFusedHeading());
    frc::SmartDashboard::PutNumber("Chassis/Left Position", leftMaster.GetSelectedSensorPosition());
    frc::SmartDashboard::PutNumber("Chassis/Right Position", rightMaster.GetSelectedSensorPosition());
    frc::SmartDashboard::PutNumber("Chassis/Left Speed", leftMaster.GetSelectedSensorVelocity());
    frc::SmartDashboard::PutNumber("Chassis/Right Speed", rightMaster.GetSelectedSensorVelocity());
    frc::Rotation2d gyroRot2d = frc::Rotation2d (units::degree_t(-gyro.GetAngle()));
    odometry.Update(gyroRot2d, units::meter_t(leftMaster.GetSelectedSensorPosition()),
    units::meter_t(rightMaster.GetSelectedSensorPosition()));
}

void Chassis::arcadeDrive(double linear, double angular) {
    leftMaster.Set(linear + angular);
    rightMaster.Set(linear - angular);
}

void Chassis::tankDrive(double leftSpeed, double rightSpeed){
    leftMaster.Set(leftSpeed);
    rightMaster.Set(rightSpeed);
}

void Chassis::voltageDrive(double leftVoltage, double rightVoltage){
    leftMaster.SetVoltage(units::volt_t(leftVoltage));
    rightMaster.SetVoltage(units::volt_t(rightVoltage));  
    
}

double Chassis::getYaw() {
    return gyro.GetYaw();
}

frc2::RamseteCommand Chassis::getRamsetteCommand(frc::Trajectory trajectory){
frc::DifferentialDriveVoltageConstraint autoVoltageConstraint(
      frc::SimpleMotorFeedforward<units::meters>(
          DriveConstants::ks, DriveConstants::kv, DriveConstants::ka),
      DriveConstants::kDriveKinematics, 10_V);

  // Set up config for trajectory
  frc::TrajectoryConfig config(AutoConstants::kMaxSpeed,
                               AutoConstants::kMaxAcceleration);
  // Add kinematics to ensure max speed is actually obeyed
  config.SetKinematics(DriveConstants::kDriveKinematics);
  // Apply the voltage constraint
  config.AddConstraint(autoVoltageConstraint);

  // An example trajectory to follow.  All units in meters.
  auto exampleTrajectory = frc::TrajectoryGenerator::GenerateTrajectory(
      // Start at the origin facing the +X direction
      frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
      // Pass through these two interior waypoints, making an 's' curve path
      {frc::Translation2d(1_m, 1_m), frc::Translation2d(2_m, -1_m)},
      // End 3 meters straight ahead of where we started, facing forward
      frc::Pose2d(3_m, 0_m, frc::Rotation2d(0_deg)),
      // Pass the config
      config);

    return frc2::RamseteCommand(
      exampleTrajectory, [this]() { return getPose(); },
      frc::RamseteController(ChassisMap::kRamseteB,
                             ChassisMap::kRamseteZeta),
      frc::SimpleMotorFeedforward<units::meters>(
          DriveConstants::ks, DriveConstants::kv, DriveConstants::ka),
      DriveConstants::kDriveKinematics,
      [this] { return m_drive.GetWheelSpeeds(); },
      frc2::PIDController(DriveConstants::kPDriveVel, 0, 0),
      frc2::PIDController(DriveConstants::kPDriveVel, 0, 0),
      [this](auto left, auto right) { m_drive.TankDriveVolts(left, right); },
      {&m_drive});
    
}

frc::Pose2d Chassis::getPose() {
    return odometry.GetPose();
}