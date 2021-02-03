//
// Created by ajahueym on 1/25/21.
//

#ifndef BOTBUSTERS_REBIRTH_ECTOGAZEBOPISTON_H
#define BOTBUSTERS_REBIRTH_ECTOGAZEBOPISTON_H
#include "EctoPiston.h"
#include <networktables/NetworkTable.h>
#include <frc/Notifier.h>

class EctoGazeboPiston : public EctoPiston{
public:
	
	class UpdateManager{
	public:
		void addGazeboPiston(EctoGazeboPiston* piston);
		void removeGazeboMotor(EctoGazeboPiston* piston);
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
		std::vector<EctoGazeboPiston*> createdGazeboPistons;
		std::shared_ptr<frc::Notifier> enabledNotifier;
		std::mutex updateMutex, nextToAccessMutex, lowPriorityMutex;
	};
	
	EctoGazeboPiston(const std::string& robot, const std::string& piston);
	void setState(bool state) override;
	void toggleState() override;
	bool getState() override;
	~EctoGazeboPiston();
private:
	UpdateManager& updateManager = EctoGazeboPiston::UpdateManager::getInstance();
	
	std::atomic<bool> wantedState{};
	nt::NetworkTableEntry pistonEntry;
};


#endif //BOTBUSTERS_REBIRTH_ECTOGAZEBOPISTON_H
