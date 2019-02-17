// Copyright 2018 Iuga Florin

#ifndef COMANDA_H_

#define COMANDA_H_

#include <string>

class Comanda {
 public:
	std::string commandType;
	int robotID;
	int nrBoxes;
	int x;
	int y;
	int priority;
	int time;

	Comanda() {
	}

	Comanda(const Comanda &other) {
		this->commandType = other.commandType;
		this->robotID = other.robotID;
		this->nrBoxes = other.nrBoxes;
		this->priority = other.priority;
		this->x = other.x;
		this->y = other.y;
		this->time = other.time;
	}

	Comanda& operator=(const Comanda& other) {
		if(this != &other){
		this->commandType = other.commandType;
		this->robotID = other.robotID;
		this->nrBoxes = other.nrBoxes;
        this->priority = other.priority;
		this->x = other.x;
		this->y = other.y;
		this->time = other.time;
		}
		return *this;
	}
};

#endif  // COMANDA_H_
