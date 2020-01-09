#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/Timer.h>
#include "subsystems/Chassis.h"

class MoveAngularTimed
    : public frc2::CommandHelper<frc2::CommandBase, MoveAngularTimed> {
 public:
    
 explicit MoveAngularTimed(Chassis* chassis, int time, double power);

 void Initialize() override;

 void Execute() override;

 void End(bool interrupted) override; 

 bool IsFinished() override;

 private:
  Chassis* chassis;
  double startTime = 0.0;
  double desiredTime = 0.0;
  double power = 0.0;
};