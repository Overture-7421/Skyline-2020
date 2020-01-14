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
        static const unsigned int LEFT_1 = 4;
        static const unsigned int LEFT_2 = 5;
        static const unsigned int RIGHT_1 = 2;
        static const unsigned int RIGHT_2 = 3;
        static constexpr float RAMP_RATE = 1.0/10.0;
        static constexpr double ENC_METER_PER_PULSE = 1; ///TODO MEASURE
        static constexpr auto TRACK_WIDTH = 0.71_m;
        static constexpr auto kMaxSpeed = 3_mps;
        static constexpr auto kMaxAcceleration = 3_mps_sq;
        static constexpr double kRamseteB = 2;
        static constexpr double kRamseteZeta = 0.7;
        static constexpr double kPDriveVel = 0;
        static constexpr auto ks = 0_V;
        static constexpr auto kv = 0 * 1_V * 1_s / 1_m;
        static constexpr auto ka = 0 * 1_V * 1_s * 1_s / 1_m;
};

class OI {
    public:
         static const int DRIVER1_PORT = 0;
};
