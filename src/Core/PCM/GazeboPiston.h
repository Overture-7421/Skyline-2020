//
// Created by ajahueym on 1/25/21.
//

#ifndef BOTBUSTERS_REBIRTH_ECTOGAZEBOPISTON_H
#define BOTBUSTERS_REBIRTH_ECTOGAZEBOPISTON_H
#include "EctoPiston.h"
#include <networktables/NetworkTable.h>
#include <frc/Notifier.h>
#include <atomic>
#include <memory>

class GazeboPiston : public EctoPiston{
public:
	
	class UpdateManager{
	public:
		void addGazeboPiston(GazeboPiston* piston);
		void removeGazeboMotor(GazeboPiston* piston);
		static UpdateManager &getInstance() {
			static UpdateManager instance;
			return instance;
		}
		UpdateManager(UpdateManager const &) = delete;
		UpdateManager &operator=(UpdateManager const &) = delete;
		~UpdateManager();
	private:
		explicit UpdateManager();
		std::atomic <bool> runningEnabledNotifier{true};
		std::atomic <bool> ntConnected {false};
		std::vector<GazeboPiston*> createdGazeboPistons;
		std::shared_ptr<frc::Notifier> enabledNotifier;
		std::mutex updateMutex, nextToAccessMutex, lowPriorityMutex;
	};
	
	GazeboPiston(const std::string& robot, const std::string& piston);
	void setState(bool state) override;
	void toggleState() override;
	bool getState() override;
	~GazeboPiston();
private:
	UpdateManager& updateManager = GazeboPiston::UpdateManager::getInstance();
	
	std::atomic<bool> wantedState{};
	nt::NetworkTableEntry pistonEntry;
};


#endif //BOTBUSTERS_REBIRTH_ECTOGAZEBOPISTON_H
