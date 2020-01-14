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
frc::DifferentialDriveWheelSpeeds Chassis::getWheelSpeeds() {
    frc::DifferentialDriveWheelSpeeds wheelspeeds;
    wheelspeeds.left = units::meters_per_second_t(leftMaster.GetSelectedSensorVelocity());
    wheelspeeds.right = units::meters_per_second_t(rightMaster.GetSelectedSensorVelocity());
    return wheelspeeds;
}
void Chassis::arcadeDrive(double linear, double angular) {
    leftMaster.Set(linear + angular);
    rightMaster.Set(linear - angular);
}

void Chassis::tankDrive(double leftSpeed, double rightSpeed){
    leftMaster.Set(leftSpeed);
    rightMaster.Set(rightSpeed);
}

void Chassis::voltageDrive(units::volt_t leftVoltage, units::volt_t rightVoltage){
    leftMaster.SetVoltage(leftVoltage);
    rightMaster.SetVoltage(rightVoltage);  
    
}

double Chassis::getYaw() {
    return gyro.GetYaw();
}

std::unique_ptr<frc2::SequentialCommandGroup> Chassis::getRamsetteCommand(const Pose2d& start, const std::vector<Translation2d>& interiorWaypoints, const Pose2d& end){
    frc::DifferentialDriveVoltageConstraint autoVoltageConstraint(
        frc::SimpleMotorFeedforward<units::meters>(
            ChassisMap::ks, ChassisMap::kv, ChassisMap::ka),
        kinematics, 10_V);

  // Set up config for trajectory
  frc::TrajectoryConfig config(ChassisMap::kMaxSpeed,
                               ChassisMap::kMaxAcceleration);
  // Add kinematics to ensure max speed is actually obeyed
  config.SetKinematics(kinematics);
  // Apply the voltage constraint
  config.AddConstraint(autoVoltageConstraint);
  auto targetTrajectory = frc::TrajectoryGenerator::GenerateTrajectory(start, interiorWaypoints, end, config);

    auto commandGroup = std::make_unique<frc2::SequentialCommandGroup>();
    commandGroup->AddCommands(
        frc2::RamseteCommand(
            targetTrajectory, [this]() { return getPose(); },
            frc::RamseteController(ChassisMap::kRamseteB,
                                    ChassisMap::kRamseteZeta),
            frc::SimpleMotorFeedforward<units::meters>(
                ChassisMap::ks, ChassisMap::kv, ChassisMap::ka),
            kinematics,
            [this] { return getWheelSpeeds(); },
            frc2::PIDController(ChassisMap::kPDriveVel, 0, 0),
            frc2::PIDController(ChassisMap::kPDriveVel, 0, 0),
            [this](auto left, auto right) { voltageDrive(left, right); },
            {this}
        ),
        frc2::RunCommand(
            [this]() {tankDrive(0,0);}, this
        )
    );
    return commandGroup;
}

frc::Pose2d Chassis::getPose() {
    return odometry.GetPose();
}