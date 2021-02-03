//
// Created by ajahueym on 1/25/21.
//

#include "EctoGazeboPiston.h"
#include <networktables/NetworkTableInstance.h>
#include <frc/DriverStation.h>

EctoGazeboPiston::EctoGazeboPiston(const std::string& robot, const std::string& piston) : EctoPiston(robot + "/" + piston) {
	
	static auto ntInstance = nt::NetworkTableInstance::GetDefault();
	pistonEntry = ntInstance.GetTable(robot)->GetSubTable(piston)->GetEntry("State");
	updateManager.addGazeboPiston(this);
#ifndef SIMULATION
	log->warn("Using >EctoGazeboPiston in a non simulated project! This is for Gazebo and Simulations! Piston Name: {}", getName());
#endif
}

void EctoGazeboPiston::setState(bool state) {
	wantedState = state;
}

void EctoGazeboPiston::toggleState() {
	setState(!getState());
}

bool EctoGazeboPiston::getState() {
	return pistonEntry.GetBoolean(false);
}

EctoGazeboPiston::~EctoGazeboPiston() {
	updateManager.removeGazeboMotor(this);
}

EctoGazeboPiston::UpdateManager::UpdateManager() {
	static auto ntInstance = nt::NetworkTableInstance::GetDefault();
	ntInstance.AddConnectionListener([this](const nt::ConnectionNotification& notification) {
		if(notification.connected){
			ntConnected = true;
		}
	}, true);
	
	enabledNotifier = std::make_shared<frc::Notifier>([this]{
		log->info("Gazebo Piston UpdateManager waiting for Network Tables to connect...");
		auto start = std::chrono::high_resolution_clock::now();
		double timeoutCounter = 0;
		
		while(!ntConnected && runningEnabledNotifier){
			timeoutCounter = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();
			
			if(timeoutCounter > 20.0){
				log->error("Gazebo Piston UpdateManager couldn't connect to NetworkTables! It wont run...");
				return;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
		}
		log->info("Gazebo Piston UpdateManager connected!");
		static const frc::DriverStation& driverStation = frc::DriverStation::GetInstance();
		
		while(runningEnabledNotifier){
			std::lock_guard lowGuard(lowPriorityMutex);
			std::unique_lock nextToAccess(nextToAccessMutex);
			std::lock_guard updateGuard(updateMutex);
			
			nextToAccess.unlock();
			
			if(driverStation.IsEnabled()){
				for(const auto& piston : createdGazeboPistons){
					if(!piston->pistonEntry.Exists()){
						log->error("Trying to control non existent/invalid Gazebo Piston, its state entry doesnt exist! {}", piston->getName());
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

void EctoGazeboPiston::UpdateManager::addGazeboPiston(EctoGazeboPiston *piston) {
	std::unique_lock nextGuard(nextToAccessMutex);
	std::lock_guard guard(updateMutex);
	
	nextGuard.unlock();
	const auto& iterator = std::find(createdGazeboPistons.begin(), createdGazeboPistons.end(), piston);
	if(iterator != createdGazeboPistons.end()){
		log->warn("Tried to add a Gazebo Piston twice to the UpdateManager!");
		return;
	}
	createdGazeboPistons.emplace_back(piston);
}

void EctoGazeboPiston::UpdateManager::removeGazeboMotor(EctoGazeboPiston *piston) {
	std::unique_lock nextGuard(nextToAccessMutex);
	std::lock_guard guard(updateMutex);
	
	nextGuard.unlock();
	const auto& iterator = std::find(createdGazeboPistons.begin(), createdGazeboPistons.end(), piston);
	if(iterator == createdGazeboPistons.end()){
		log->warn("Tried remove a Gazebo Piston that wasn't in UpdateManager!");
		return;
	}
	createdGazeboPistons.erase(iterator);
}

EctoGazeboPiston::UpdateManager::~UpdateManager() {
	runningEnabledNotifier = false;
	enabledNotifier->Stop();
	std::lock_guard lowGuard(lowPriorityMutex);
	std::unique_lock nextToAccess(nextToAccessMutex);
	std::lock_guard updateGuard(updateMutex);
}

