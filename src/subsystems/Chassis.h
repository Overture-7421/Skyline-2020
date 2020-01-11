#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <AHRS.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>


using namespace ctre::phoenix::motorcontrol::can;
using namespace ctre::phoenix::motorcontrol;

class Chassis : public frc2::SubsystemBase {
 public:
  Chassis();
  void arcadeDrive(double linear, double angular);
  void tankDrive(double leftSpeed, double rightSpeed);
  double getYaw();
  frc::Pose2d getPose();

 private:
  AHRS gyro {SPI::Port::kMXP};
  WPI_TalonSRX rightMaster {1};
  WPI_TalonSRX leftMaster {4};

  WPI_VictorSPX rightMotor1 {2};
  WPI_VictorSPX rightMotor2 {3};

  WPI_VictorSPX leftMotor1 {5};
  WPI_VictorSPX leftMotor2 {6};

  frc::SpeedControllerGroup left{leftMaster, leftMotor1, leftMotor2};
  frc::SpeedControllerGroup right{rightMaster, rightMotor1, rightMotor2};
  frc::DifferentialDrive differentialDrive{left, right};

};
