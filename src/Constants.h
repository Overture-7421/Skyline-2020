/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <units/units.h>

class ChassisMap
{
public:
    static const unsigned int RIGHT_MASTER = 7;
    static const unsigned int LEFT_MASTER = 14;
    static const unsigned int LEFT_1 = 15;
    static const unsigned int LEFT_2 = 16;
    static const unsigned int RIGHT_1 = 8;
    static const unsigned int RIGHT_2 = 9;
    static constexpr float RAMP_RATE = 1.0 / 4.0;
    static constexpr double ENC_METER_PER_PULSE = 0.001419446;
    static constexpr auto TRACK_WIDTH = 1.0_m;
    static constexpr auto kMaxSpeed = 3.0_mps;
    static constexpr auto kMaxAcceleration = 4_mps_sq;
    static constexpr double kRamseteB = 2;
    static constexpr double kRamseteZeta = 0.7;
    static constexpr double kPDriveVel = 2.0;
    static constexpr auto ks = 1.7_V;
    static constexpr auto kv = 0.472 * 1_V * 1_s / 1_m;
    static constexpr auto ka = 0 * 1_V * 1_s * 1_s / 1_m;
    static const auto peakCurrentLimit = 100;
    static const int continuousCurrentLimit = 75;
};

class FeederMap
{
public:
    static const unsigned int FEEDER_MOTOR = 10;
};

class StorageMap
{
public:
    static const unsigned int STORAGE_MOTOR = 4;
};

class ShooterMap
{
public:
    static const unsigned int MASTER_RIGHT = 1;
    static const unsigned int RIGHT_1 = 2;
    static const unsigned int LEFT_1 = 13;
    static const unsigned int FEEDER = 12;
};

class OI
{
public:
    static const int DRIVER1_PORT = 0;
};