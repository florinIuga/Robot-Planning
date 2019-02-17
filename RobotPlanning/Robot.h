// Copyright 2018 Iuga Florin

#ifndef ROBOT_H_

#define ROBOT_H_

#include "Dequeue.h"
#include "Comanda.h"
#include <fstream>

class Robot {
 public:
	// fiecare Robot are o coada
	Dequeue<Comanda> queue;
	int nrBoxes;

	Robot() {
		this->nrBoxes = 0;
	}
	~Robot() {
	}

	void printCommands(std::ofstream &out) {
		// ma pozitionez la inceputul cozii
		Node<Comanda> *temp = queue.getHead();

		while (temp->next != NULL) {
			out << temp->comanda.commandType << " "
                            << temp->comanda.x << " " << temp->comanda.y << " "
                            << temp->comanda.nrBoxes << "; ";
			temp = temp->next;
		}
		out << temp->comanda.commandType << " " << temp->comanda.x
                    << " " << temp->comanda.y << " " << temp->comanda.nrBoxes;
		out << '\n';
	}
	// functia pentru HOW MANY BOXES
	int getNrBoxes() {
		return this->nrBoxes;
	}
};

#endif  // ROBOT_H_
