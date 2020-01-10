#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <AHRS.h>
#include <frc/Encoder.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "RobotMap.h"
#include <frc/controller/PIDController.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>

#include <frc/controller/RamseteController.h>
#include <frc/trajectory/TrajectoryGenerator.h>

using namespace ctre::phoenix::motorcontrol::can;
using namespace ctre::phoenix::motorcontrol;

class Chassis : public frc2::SubsystemBase {
 public:
  Chassis();
  void Periodic() override;
  void UpdateBoard();
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void drive(double linear, double angular);
  
  double getYaw();

 private:
  double kp = 0.5;
  double kd = 0.0004;
  double ki = 0.2;
  WPI_VictorSPX leftMotor {ChassisMap::LEFTM};
  WPI_VictorSPX rightMotor {ChassisMap::RIGHTM};
  WPI_VictorSPX leftMotor1 {ChassisMap::RIGHTM1};
  WPI_VictorSPX rightMotor1 {ChassisMap::RIGHTM1};
  frc::Encoder leftEncoder{ChassisMap::ENC_L_A,ChassisMap::ENC_L_B};
  frc::Encoder rightEncoder{ChassisMap::ENC_R_A,ChassisMap::ENC_R_B};
  frc::SpeedControllerGroup left{leftMotor, leftMotor1};
  frc::SpeedControllerGroup right{rightMotor, rightMotor1};
  frc::DifferentialDrive differentialDrive{left, right};
  frc2::PIDController leftPID{kp,ki,kd,units::second_t(5_ms)};
  frc2::PIDController rightPID{kp,ki,kd,units::second_t(5_ms)};
  double linear = 0;
  double angular = 0;
  AHRS gyro{SPI::Port::kMXP};
  frc::DifferentialDriveOdometry odometry{ frc::Rotation2d (units::degree_t(-gyro.GetAngle()))};
  DifferentialDriveKinematics kinematis {units::meter_t(0.5)};
  frc::Pose2d pose;
  frc::RamseteController ramsete;
  frc::Trajectory targetTrajectory;
};