#include "Chassis.h"

Chassis::Chassis(){

}
void Chassis::Periodic(){
 rightMotor.Set(ControlMode::PercentOutput,.2);
 leftMotor.Set(ControlMode::PercentOutput,.2);
 rightMotor1.Set(ControlMode::PercentOutput,.2);
 leftMotor1.Set(ControlMode::PercentOutput,.2);
}
