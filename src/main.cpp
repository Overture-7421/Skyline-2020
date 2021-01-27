#include "Robots/Skyline.h"
#include <networktables/NetworkTableInstance.inl>

#ifndef RUNNING_FRC_TESTS
int main() {

#ifdef SIMULATION

    if (std::strcmp(NT_REMOTE_SERVER, "127.0.0.1") != 0) {
        std::cout << "Running with remote NT server " <<  NT_REMOTE_SERVER << "!\n";
        NT_StartClient(NT_GetDefaultInstance(), NT_REMOTE_SERVER, NT_REMOTE_PORT);
    }
    NT_SetUpdateRate(NT_GetDefaultInstance(), 0.01);  // Set update rate to quickest possible (Limited by NT)
    std::cout << "Running in simulation mode!\n";
#endif

    return frc::StartRobot<Skyline>();
}
#endif