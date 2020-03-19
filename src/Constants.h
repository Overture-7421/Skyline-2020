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
    static constexpr auto TRACK_WIDTH = 0.7_m;
    static constexpr auto kMaxSpeed = 3_mps;
    static constexpr auto kMaxAcceleration = 3_mps_sq;
    static constexpr auto ks = 1.7_V;
    static constexpr auto kv = 0.472 * 1_V * 1_s  / 1_m;
    static constexpr auto ka = 0 * 1_V * 1_s * 1_s / 1_m;
    static const auto peakCurrentLimit = 100;
    static const auto continuousCurrentLimit = 30;
};

/*Create Map for respective subsystem*/


class OI
{
public: 
    static const int DRIVER1_PORT = 0;
};

