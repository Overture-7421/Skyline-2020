// /*----------------------------------------------------------------------------*/
// /* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
// /* Open Source Software - may be modified and shared by FRC teams. The code   */
// /* must be accompanied by the FIRST BSD license file in the root directory of */
// /* the project.                                                               */
// /*----------------------------------------------------------------------------*/

// #include "Panic.h"

// Panic::Panic(Shooter* shooter, double amount = 0) {

//   this->shooter = shooter;
//   this->amount = amount;

// }


// // Called when the command is initially scheduled.
// void Panic::Initialize() {

//   shooter.feed(0);

// }

// // Called repeatedly when this Command is scheduled to run
// void Panic::Execute() {

//   shooter.feed(-amount);

// }

// // Called once the command ends or is interrupted.
// void Panic::End(bool interrupted) {

//   shooter.feed(0);

// }

// // Returns true when the command should end.
// bool Panic::IsFinished() { return false; }
