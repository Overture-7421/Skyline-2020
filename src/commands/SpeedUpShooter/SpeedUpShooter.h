#pragma once

#include <subsystems/Shooter/Shooter.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

class SpeedUpShooter
    : public frc2::CommandHelper<frc2::CommandBase, SpeedUpShooter> {
 public:

  explicit SpeedUpShooter(Shooter* shooter, double targetRPS);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
  Shooter* shooter;
  double targetRPS;




};
