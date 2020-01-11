#pragma once

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

  explicit TeleopDrive(Chassis* chassis);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override; 

  bool IsFinished() override;

 private:
    XboxController control {0};
    Chassis* chassis;
    frc2::PIDController angleController {0,0,0, units::second_t(5_ms)};
    double targetAngle = 0.0;
};