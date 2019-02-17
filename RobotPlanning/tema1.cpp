// Copyright 2018 Iuga Florin

#include <iostream>
#include "Stack.h"
#include "Robot.h"
#include <cstdio>
#include <string>
#include <fstream>


void execute(Robot *robots, int robotID, Stack<Comanda> *stack1,
    Stack<Comanda> *stack2, int **map, int time, std::ofstream &out) {
	Node<Comanda> *temp = robots[robotID].queue.getHead();
	Comanda comanda;
	int x, y, firstNrBoxes;
	int nrBoxesPerCom = 0;
	std::string commandType, commandExecuted;

		// verific mai intai daca coada robotului cu id-ul robotID este
                // goala, atunci afisez mesajul
		 if (robots[robotID].queue.isEmpty())
		 {
		 	out << "EXECUTE: No command to execute" << std::endl;
		 } else {
		 	// obtin valorile din prima comanda a robotului cu id-ul robotID
				 commandType = temp->comanda.commandType;
				 comanda.commandType = commandType;
				 x = temp->comanda.x;
				 y = temp->comanda.y;
				 // numarul de cutii care trebuiesc ridicate/lasate
				 firstNrBoxes = temp->comanda.nrBoxes;
				 comanda.time = time - temp->comanda.time;
				 comanda.x = x;
				 comanda.y = y;
				 comanda.robotID = robotID;
		 	// verific daca comanda este de tip GET sau DROP
		 	 if (commandType.compare("GET") == 0) {
		 		if (map[x][y] > firstNrBoxes) {
		 			robots[robotID].nrBoxes += firstNrBoxes;
		 			map[x][y] -= firstNrBoxes;
		 			nrBoxesPerCom = firstNrBoxes;
		 			comanda.nrBoxes = nrBoxesPerCom;

		 		} else {
		 			// daca nu exista pe pozitia (x,y) un
                                        // numar de cutii >= numarul de cutii
                                        // care sunt necesare spre a fi
                                        // ridicate, luam toate cutiile
                                        // disponibile pe pozitia respectiva
		 			robots[robotID].nrBoxes += map[x][y];
		 			nrBoxesPerCom = map[x][y];
		 			map[x][y] = 0;
		 			comanda.nrBoxes = nrBoxesPerCom;
		 		}
		 		  // o scot din coada
		 	      robots[robotID].queue.removeFirst();

		   	 } else if (commandType.compare("DROP") == 0) {
		 		// cand robotul nu are numarul de cutii
                                // necesare atunci lasa tot ce are pe pozitia
                                // respectiva
		 		if (firstNrBoxes >= robots[robotID].nrBoxes) {
		 			map[x][y] += robots[robotID].nrBoxes;
		 			nrBoxesPerCom = robots[robotID].nrBoxes;
		 			robots[robotID].nrBoxes = 0;
		 			comanda.nrBoxes = nrBoxesPerCom;
		 		} else {
		 			map[x][y] += firstNrBoxes;
		 			robots[robotID].nrBoxes -= firstNrBoxes;
		 			nrBoxesPerCom = firstNrBoxes;
		 			comanda.nrBoxes = nrBoxesPerCom;
		 		}
		 		// o scot din coada
		 		robots[robotID].queue.removeFirst();
		 	}
		 	// introduc comanda in stiva de comenzi executate
		 	stack2->push(comanda);
		 	comanda.robotID = robotID;
			comanda.x = -1;
			comanda.y = -1;
			comanda.nrBoxes = -1;
			comanda.priority = -1;
			comanda.time =  -1;
			comanda.commandType = "EXECUTE";
			stack1->push(comanda);
		 }
}

void undo(Robot *robots, int **map, Stack<Comanda> *stack1,
    Stack<Comanda> *stack2, int time, std::ofstream &out){
    	Comanda comanda;
    	int ID, x, y, nrBoxes, priority;
    	int ID2;
    	// ID2->id -ul de la ultima comanda din istoric
    	std::string commandType;
    	std::string commandExecuted;
    	comanda.time = time;

    	if (stack1->isEmpty()) {
    		out << "UNDO: No History" << std::endl;
    	} else {
    		commandType = stack1->peek().commandType;
    	 	priority = stack1->peek().priority;
    	 	// obtin id-ul de la ultima comanda din istoric de tip ADD sau GET
    	 	ID2 = stack1->peek().robotID;

    	  if (commandType.compare("EXECUTE") == 0)
    	  {
    		// obtin valorile ultimei comenzi executate, daca stiva de
                // comenzi executate nu este goala
    	  	if (!stack2->isEmpty()) {
    	  		x = stack2->peek().x;
    			y = stack2->peek().y;
    			nrBoxes = stack2->peek().nrBoxes;
    			ID = stack2->peek().robotID;
    			comanda.robotID = ID;
    			commandExecuted = stack2->peek().commandType;  // GET sau DROP
				comanda.x = x;
    			comanda.y = y;
    			comanda.nrBoxes = nrBoxes;
    			comanda.commandType = commandExecuted;

    			if (commandExecuted.compare("GET") == 0) {
    	  			// repun cutiile pe pozitia lor
    				map[x][y] += nrBoxes;
    				// cutiile robotului cu id ul ID vor scadea cu
                                // numarul de cutii pe care le luase initial
    				robots[ID].nrBoxes -= nrBoxes;
					// adaug LAST EXECUTED COMMAND in coada robotului cu id-ul ID
    		   		robots[ID].queue.addFirst(comanda);
    				// acum comanda respectiva nu mai este considerata ca fiind executata
			   		stack2->pop();
    	  		} else if (commandExecuted.compare("DROP") == 0) {
    	  			// scad nr de cutii de pe pozitia (x,y) cu
                                // numarul de cutii pe care trebuia sa le lase
                                // initial robotul
    				map[x][y] -= nrBoxes;
    				// inapoiez cutiile robotului cu id ul ID
    				robots[ID].nrBoxes += nrBoxes;
    				// adaug LAST EXECUTED COMMAND in coada robotului cu id-ul ID
    		   		robots[ID].queue.addFirst(comanda);
    				// acum comanda respectiva nu mai este considerata ca fiind executata
			   		stack2->pop();
    			}
			}
    		// scot comanda EXECUTE din stiva de comenzi
    		stack1->pop();
    	  }

    	  if (commandType.compare("GET") == 0)
    	  {
    	  	if (priority == 0) {
    	  		// scot comanda din coada, prin fata
    	  		robots[ID2].queue.removeFirst();

    	  	} else if (priority == 1) {
				// scot comanda din coada, prin spate
    	  		robots[ID2].queue.removeLast();
    	  	}
    		// o scot  din stiva de istoric
			stack1->pop();
		  }
    	  if (commandType.compare("DROP") == 0)
    	  {
    		if (priority == 0) {
    	  		// scot comanda din coada, prin fata
    	  		robots[ID2].queue.removeFirst();
    	  	} else if (priority == 1) {
    	  		// scot comanda din coada, prin spate
    	  		robots[ID2].queue.removeLast();
    	  	}
    		// o scot din stiva de istoric
    		stack1->pop();
    	  }
    	}
}
    // folosesc stiva a2a, adica stack2 care contine comenzile executate
void lastExecutedCommand(Stack<Comanda> *stack2, std::ofstream &out){
    	int ID = stack2->peek().robotID;
    	if (stack2->isEmpty()) {
    		out << "LAST_EXECUTED_COMMAND: No command was executed" << std::endl;
    	} else {
    		out << "LAST_EXECUTED_COMMAND: " << ID << ": " <<
                    stack2->peek().commandType << " " << stack2->peek().x << " "
                    << stack2->peek().y << " " << stack2->peek().nrBoxes
                    << std::endl;
    	}
}
void howMuchTime(Stack<Comanda> *stack2, std::ofstream &out) {
	if (stack2->isEmpty()) {
		out << "HOW_MUCH_TIME: No command was executed" << std::endl;
	} else {
		out << "HOW_MUCH_TIME: " << stack2->peek().time - 1 << std::endl;
	}
}

int main() {
	Comanda comanda;
	Stack<Comanda> stack1;  // stiva pentru comenzile ADD si Execute
	Stack<Comanda> stack2;  // stiva pentru comenzile executate
	int N;
	int LIN, COL;
	int **map;
	int robotID;
	std::string commandType;
	int x, y;
	int nrBoxes;
	int priority;
	int time = 0;
	std::ifstream in("robots.in");
	std::ofstream out("robots.out");
	in >> N;
	Robot robots[N];
	in >> LIN;
	in >> COL;
	int i, j;
	map = new int*[LIN];
	for (int i = 0; i < LIN; i++) {
		map[i] = new int[COL];
	}
	for (i = 0; i < LIN; ++i)
	{
		for (j = 0; j < COL; ++j)
		{
			in >> map[i][j];
		}
	}
	while (in >> commandType) {
		if (commandType.compare("ADD_GET_BOX") == 0 ||
                    commandType.compare("ADD_DROP_BOX") == 0) {
		   in >> robotID;
	       in >> x;
	       in >> y;
	       in >> nrBoxes;
	       in >> priority;
	       if ((commandType.compare("ADD_GET_BOX")) == 0)
	       {
	       	 comanda.commandType = "GET";
	       } else if ((commandType.compare("ADD_DROP_BOX")) == 0) {
	       	comanda.commandType = "DROP";
	       }

	       comanda.robotID = robotID;
           comanda.x = x;
	       comanda.y = y;
	       comanda.nrBoxes = nrBoxes;
	       comanda.priority = priority;
	       comanda.time = time;

	       if (comanda.priority == 0) {
		    robots[robotID].queue.addFirst(comanda);
		    // adaug in stiva de comenzi de tip ADD si EXECUTE
		    stack1.push(comanda);
		   } else if (comanda.priority == 1) {
		   	robots[robotID].queue.addLast(comanda);
		   	stack1.push(comanda);
		   }
		   time++;
		}
		if (commandType.compare("EXECUTE") == 0) {
			in >> robotID;
			comanda.robotID = robotID;
			time++;
			execute(robots, robotID, &stack1, &stack2, map, time, out);
		}
		if (commandType.compare("UNDO") == 0) {
			undo(robots, map, &stack1, &stack2, time, out);
			time++;
		}
		if (commandType.compare("LAST_EXECUTED_COMMAND") == 0) {
			lastExecutedCommand(&stack2, out);
			time++;
		}
		if (commandType.compare("PRINT_COMMANDS") == 0)
		{
			in >> robotID;
			if (robots[robotID].queue.isEmpty()) {
				out << "PRINT_COMMANDS: No command found" << std::endl;
			} else {
				out << "PRINT_COMMANDS: " << robotID << ": ";
				robots[robotID].printCommands(out);
			}
			time++;
		}
		if (commandType.compare("HOW_MANY_BOXES") == 0)
		{
			in >> robotID;
			out << "HOW_MANY_BOXES: " << robots[robotID].getNrBoxes() << std::endl;
			time++;
		}
		if (commandType.compare("HOW_MUCH_TIME") == 0)
		{
			howMuchTime(&stack2, out);
			time++;
		}
	}
	for (int i = 0; i < LIN; ++i)
	{
		delete[] map[i];
	}
	delete[] map;

	return 0;
}

