//Dylan Dennison
//Prototype lab 10
//04/2/21

#include <deque>
#include <cstdlib>
#include <time.h>
#include "State.hpp"

using std::deque; 


int main() {
	srand(time(nullptr));

	deque<Process*> waitingQ;
	deque<Process*> readyQ;  //queues 

	Process pPrototype;  //protoype process

	//filling
	for (int i = 0; i < 4; ++i) {
		readyQ.push_back(pPrototype.clone());
	}

	//setting id
	for (int i = 0; i < readyQ.size(); ++i) {
		readyQ[i]->pID(i);
	}

	// setting all 4 processes to ready 
	for (int i = 0; i < readyQ.size(); ++i) {
		readyQ[i]->report(); 

		readyQ[i]->admitted();

		readyQ[i]->report();
		cout << endl;

	}
	cout << endl;


	int running, waiting; //for process decisions

	while (!readyQ.empty() || !waitingQ.empty()) {
		running = (rand() % 3) + 1; //for process decisions
		waiting = (rand() % 2) + 1;

		if (!readyQ.empty()) {
			readyQ.front()->schedulerDispatch(); //calls on head
			readyQ.front()->report();
		}

		switch(running) {

			case(1): { //terminated

				if (!readyQ.empty()) {
					readyQ.front()->exit(); //sets status
					readyQ.front()->report();
					readyQ.pop_front(); //removes

					cout << endl;
				}
				break;
			}

			case(2): { //interrupted

				if (!readyQ.empty()) {
					readyQ.front()->interrupt(); //sets status
					readyQ.front()->report();
					readyQ.push_back(readyQ.front()); //puts process to the back of the queue
					readyQ.pop_front(); //removes from front
				}
				break;
			}

			case(3): { // for IO event wait

				if (!readyQ.empty()) {
					readyQ.front()->eventWait(); //sets status 
					readyQ.front()->report();
					waitingQ.push_front(readyQ.front()); //puts into waiting queue
					readyQ.pop_front(); // removes from ready queue
				}
				break;
			}



		}

		if (waiting == 1 && !waitingQ.empty()) { //for the waiting queue decision for putting back into ready
			waitingQ.back()->eventCompletion(); //sets status
			waitingQ.back()->report();
			readyQ.push_back(waitingQ.back()); //pushs back into ready queue
			waitingQ.pop_back(); //removes
		}

	}

}
