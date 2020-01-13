#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <AHRS.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc/Encoder.h>
#include "Constants.h"
#include <frc/trajectory/Trajectory.h>
#include <frc/geometry/Pose2d.h>
#include <frc/geometry/Rotation2d.h>
#include <frc/controller/PIDController.h>
#include <frc/controller/RamseteController.h>
using namespace ctre::phoenix::motorcontrol::can;
using namespace ctre::phoenix::motorcontrol;

class Chassis : public frc2::SubsystemBase {
 public:
  Chassis();
  void arcadeDrive(double linear, double angular);
  void TankDrive(double leftSpeed, double rightSpeed);
  void Ramsete(frc::Trajectory target);
  void Periodic() override;
  double getYaw();
  frc::Pose2d getPose();
  

 private:
  AHRS gyro {SPI::Port::kMXP,50};
  WPI_TalonSRX rightMaster {1};
  WPI_TalonSRX leftMaster {4};

  WPI_VictorSPX rightMotor1 {2};
  WPI_VictorSPX rightMotor2 {3};

  WPI_VictorSPX leftMotor1 {5};
  WPI_VictorSPX leftMotor2 {6};

  frc2::PIDController leftPID{ChassisMap::KP,ChassisMap::KI, ChassisMap::KD,units::second_t(5_ms)};
  frc2::PIDController rightPID{ChassisMap::KP,ChassisMap::KI, ChassisMap::KD,units::second_t(5_ms)};
  frc::DifferentialDriveOdometry odometry{ frc::Rotation2d (units::degree_t(-gyro.GetAngle())) };
  frc::Pose2d pose;
  frc::DifferentialDriveKinematics kinematics{units::meter_t(ChassisMap::TRACK_WIDTH)};
  frc::Rotation2d gyroRot2d{units::degree_t(-gyro.GetAngle())};
  frc::SpeedControllerGroup left{leftMaster, leftMotor1, leftMotor2};
  frc::SpeedControllerGroup right{rightMaster, rightMotor1, rightMotor2};
  frc::DifferentialDrive differentialDrive{left, right};
  // frc::Encoder leftEncoder{ChassisMap::ENC_LEFT_A, ChassisMap::ENC_LEFT_B};
  // frc::Encoder rightEncoder{ChassisMap::ENC_RIGHT_A, ChassisMap::ENC_RIGHT_B};
  frc::RamseteController ramsete;
};
