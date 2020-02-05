#pragma once

#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/Chassis.h"
#include <frc/Timer.h>
#include <frc/XboxController.h>
#include <frc/controller/PIDController.h>
#include <frc2/Timer.h>


class TeleopDrive
    : public frc2::CommandHelper<frc2::CommandBase, TeleopDrive> {
 public:

  explicit TeleopDrive(Chassis* chassis, frc::XboxController* xbox);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override; 

  bool IsFinished() override;

 private:
    XboxController* control;
    Chassis* chassis;

    frc2::PIDController angleController {0.013,0,0.002};
    double targetAngle = 0.0;

   bool isValid = false;
   std::shared_ptr<nt::NetworkTable> visionTable = nt::NetworkTableInstance::GetDefault().GetTable("chameleon-vision");


   frc2::PIDController VisionController {0.015,0.00002,0.003};
   double targetVision = 0.0;
};