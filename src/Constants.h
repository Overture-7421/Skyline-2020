/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <units/units.h>

class ChassisMap {
    public:
        static const unsigned int RIGHT_MASTER = 1;
        static const unsigned int LEFT_MASTER = 4;
        static const unsigned int LEFT_1 = 5;
        static const unsigned int LEFT_2 = 6;
        static const unsigned int RIGHT_1 = 2;
        static const unsigned int RIGHT_2 = 3;
        static constexpr float RAMP_RATE = 1.0/8.0;
        static constexpr double ENC_METER_PER_PULSE = 0.001419446; 
        static constexpr auto TRACK_WIDTH = 0.7_m;
        static constexpr auto kMaxSpeed = 3.0_mps;
        static constexpr auto kMaxAcceleration = 3_mps_sq;
        static constexpr double kRamseteB = 2;
        static constexpr double kRamseteZeta = 0.7;
        static constexpr double kPDriveVel = 3.5;
        static constexpr auto ks = 0.768_V;
        static constexpr auto kv = 0.32 * 1_V * 1_s / 1_m;
        static constexpr auto ka = 0.0743 * 1_V * 1_s * 1_s / 1_m;
        static const auto peakCurrentLimit = 50;
        static const int continuousCurrentLimit = 30;
};
// class CannonMap {
//     public:
//         static const double PI  = 3.141592;
//         static const float SPHERE_DRAG_C = 0.45;
//         static const float AIR_DENSITY = 1.2754; // STP
//         static const float BALL_RADIUS = 0.0889;
// };
class OI {
    public:
         static const int DRIVER1_PORT = 0;
};
