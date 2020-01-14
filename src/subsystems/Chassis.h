#pragma once

#include <frc2/command/SubsystemBase.h>
#include "Constants.h"
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <AHRS.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc/Encoder.h>
#include "Constants.h"
#include <frc/trajectory/Trajectory.h>
#include <frc/geometry/Pose2d.h>
#include <frc/geometry/Rotation2d.h>
#include <frc/controller/RamseteController.h>
#include <frc2/command/RamseteCommand.h>
#include <frc/kinematics/DifferentialDriveWheelSpeeds.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>
#include <frc/controller/SimpleMotorFeedForward.h>
using namespace ctre::phoenix::motorcontrol::can;
using namespace ctre::phoenix::motorcontrol;

class Chassis : public frc2::SubsystemBase {
 public:
  Chassis();
  void arcadeDrive(double linear, double angular);
  void tankDrive(double leftSpeed, double rightSpeed);
  void voltageDrive(units::volt_t leftVoltage, units::volt_t rightVoltage); //Used for Ramsette
  void Periodic() override;
  double getYaw();
  frc::DifferentialDriveWheelSpeeds getWheelSpeeds();
  frc::Pose2d getPose();
  frc2::RamseteCommand getRamsetteCommand(frc::Trajectory trajectory);

 private:
  AHRS gyro {SPI::Port::kMXP};
  WPI_TalonSRX rightMaster {ChassisMap::RIGHT_MASTER};
  WPI_TalonSRX leftMaster {ChassisMap::LEFT_MASTER};

  WPI_VictorSPX rightMotor1 {ChassisMap::RIGHT_1};
  WPI_VictorSPX rightMotor2 {ChassisMap::RIGHT_2};

  WPI_VictorSPX leftMotor1 {ChassisMap::LEFT_1};
  WPI_VictorSPX leftMotor2 {ChassisMap::LEFT_2};

  frc::DifferentialDriveOdometry odometry{ frc::Rotation2d (units::degree_t(-gyro.GetAngle())) };
  frc::DifferentialDriveKinematics kinematics{units::meter_t(ChassisMap::TRACK_WIDTH)};
  frc::RamseteController ramsete;
  frc::DifferentialDriveWheelSpeeds wheelSpeeds;
};
