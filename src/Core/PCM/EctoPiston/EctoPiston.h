//
// Created by ajahueym on 1/25/21.
//

#ifndef BOTBUSTERS_REBIRTH_ECTOPISTON_H
#define BOTBUSTERS_REBIRTH_ECTOPISTON_H

#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

class EctoPiston {
public:
	explicit EctoPiston(std::string name);
	virtual void setState(bool state) = 0;
	virtual void toggleState() = 0;
	virtual bool getState() = 0;
	std::string getName();
protected:
	static std::shared_ptr<spdlog::logger> log;
private:
	std::string name;
	
};


#endif //BOTBUSTERS_REBIRTH_ECTOPISTON_H
