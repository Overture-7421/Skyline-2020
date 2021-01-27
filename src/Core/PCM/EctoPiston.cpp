//
// Created by ajahueym on 1/25/21.
//

#include "EctoPiston.h"

#include <utility>
#include <iostream>

EctoPiston::EctoPiston(std::string name) : name(std::move(name)){
    std::cout << "Creating piston with name " << getName() << "...\n";
}

std::string EctoPiston::getName() {
	return name;
}
