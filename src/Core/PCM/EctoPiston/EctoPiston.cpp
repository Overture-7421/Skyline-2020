//
// Created by ajahueym on 1/25/21.
//

#include "EctoPiston.h"

#include <utility>

std::shared_ptr<spdlog::logger> EctoPiston::log = spdlog::stdout_color_mt("EctoPiston");

EctoPiston::EctoPiston(std::string name) : name(std::move(name)){
	log->trace("Creating piston with name {}...", getName());

}

std::string EctoPiston::getName() {
	return name;
}
