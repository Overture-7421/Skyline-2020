//
// Created by ajahueym on 1/25/21.
//

#include "GazeboPiston.h"
#include <networktables/NetworkTableInstance.h>
#include <frc/DriverStation.h>

GazeboPiston::GazeboPiston(const std::string& robot, const std::string& piston) : EctoPiston(robot + "/" + piston) {
	
	static auto ntInstance = nt::NetworkTableInstance::GetDefault();
	pistonEntry = ntInstance.GetTable(robot)->GetSubTable(piston)->GetEntry("State");
	updateManager.addGazeboPiston(this);
#ifndef SIMULATION
    std::cerr << "Using GazeboPiston in a non simulated project! This is for Gazebo and Simulations! Piston Name: " << getName() << "\n";
#endif
}

void GazeboPiston::setState(bool state) {
	wantedState = state;
}

void GazeboPiston::toggleState() {
	setState(!getState());
}

bool GazeboPiston::getState() {
	return pistonEntry.GetBoolean(false);
}

GazeboPiston::~GazeboPiston() {
	updateManager.removeGazeboMotor(this);
}

GazeboPiston::UpdateManager::UpdateManager() {
	static auto ntInstance = nt::NetworkTableInstance::GetDefault();
	ntInstance.AddConnectionListener([this](const nt::ConnectionNotification& notification) {
		if(notification.connected){
			ntConnected = true;
		}
	}, true);
	
	enabledNotifier = std::make_shared<frc::Notifier>([this]{
        std::cout << "Gazebo Piston UpdateManager waiting for Network Tables to connect...\n";
		auto start = std::chrono::high_resolution_clock::now();
		double timeoutCounter = 0;
		
		while(!ntConnected && runningEnabledNotifier){
			timeoutCounter = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();
			
			if(timeoutCounter > 20.0){
                std::cerr << "Gazebo Piston UpdateManager couldn't connect to NetworkTables! It wont run...\n";
				return;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
		}
        std::cout << "Gazebo Piston UpdateManager connected!\n";
		static const frc::DriverStation& driverStation = frc::DriverStation::GetInstance();
		
		while(runningEnabledNotifier){
			std::lock_guard lowGuard(lowPriorityMutex);
			std::unique_lock nextToAccess(nextToAccessMutex);
			std::lock_guard updateGuard(updateMutex);
			
			nextToAccess.unlock();
			
			if(driverStation.IsEnabled()){
				for(const auto& piston : createdGazeboPistons){
					if(!piston->pistonEntry.Exists()){
                        std::cerr << "Trying to control non existent/invalid Gazebo Piston, its state entry doesnt exist! " <<  piston->getName() << "\n";
					}else{
						piston->pistonEntry.SetBoolean(piston->wantedState);
					}
				}
			}
			
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		
	});
	enabledNotifier->StartSingle(0_s);
}

void GazeboPiston::UpdateManager::addGazeboPiston(GazeboPiston *piston) {
	std::unique_lock nextGuard(nextToAccessMutex);
	std::lock_guard guard(updateMutex);
	
	nextGuard.unlock();
	const auto& iterator = std::find(createdGazeboPistons.begin(), createdGazeboPistons.end(), piston);
	if(iterator != createdGazeboPistons.end()){
        std::cerr << "Tried to add a Gazebo Piston twice to the UpdateManager!";
		return;
	}
	createdGazeboPistons.emplace_back(piston);
}

void GazeboPiston::UpdateManager::removeGazeboMotor(GazeboPiston *piston) {
	std::unique_lock nextGuard(nextToAccessMutex);
	std::lock_guard guard(updateMutex);
	
	nextGuard.unlock();
	const auto& iterator = std::find(createdGazeboPistons.begin(), createdGazeboPistons.end(), piston);
	if(iterator == createdGazeboPistons.end()){
        std::cerr << "Tried remove a Gazebo Piston that wasn't in UpdateManager!";
		return;
	}
	createdGazeboPistons.erase(iterator);
}

GazeboPiston::UpdateManager::~UpdateManager() {
	runningEnabledNotifier = false;
}

