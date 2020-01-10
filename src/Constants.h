/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

class ChassisMap {
    public:
        static const unsigned int RIGHT_MASTER = 0;
        static const unsigned int LEFT_MASTER = 1;
        static const unsigned int LEFT_1 = 2;
        static const unsigned int LEFT_2 = 3;
        static const unsigned int RIGHT_1 = 4;
        static const unsigned int RIGHT_2 = 5;
        static constexpr float RAMP = 1/3;
};

class OI {
    public:
         static const int DRIVER1_PORT = 0;
};
