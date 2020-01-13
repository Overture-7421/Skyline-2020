// #include "Chassis2.h"

// Chassis2::Chassis2(){
//     leftEncoder.SetDistancePerPulse(ChassisMap::ENC_PPR);
//     rightEncoder.SetDistancePerPulse(0.000469043);
//     rightMotor.ConfigOpenloopRamp(1/3);
//     rightMotor1.ConfigOpenloopRamp(1/3);
//     leftMotor.ConfigOpenloopRamp(1/3);
//     leftMotor1.ConfigOpenloopRamp(1/3);
// }

// void Chassis2::Periodic(){
//     frc::Rotation2d gyroAngle{units::degree_t(-gyro.GetAngle())};
//     pose = odometry.Update(gyroAngle, units::meter_t(leftEncoder.GetDistance()),
//     units::meter_t(rightEncoder.GetDistance())); 
// }

// void Chassis2::TankDrive(double leftSpeed, double rightSpeed, bool squareInputs){
//     differentialDrive.TankDrive(leftSpeed, rightSpeed, squareInputs);
// }

// void Chassis2::ArcadeDrive(double xSpeed, double zRotation, bool squareInputs){
//     differentialDrive.ArcadeDrive(xSpeed, zRotation, squareInputs);
// }

// double Chassis2::getYaw(){
//     return gyro.GetYaw();
// }


