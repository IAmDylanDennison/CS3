//Dylan Dennison
// state
//04/02/21
#ifndef STATE_PROCESS
#define STATE_PROCESS

#include <iostream>
#include <string>

using std::string; using std::cout; using std::cin; using std::endl;


class State;

class Process {
public:
	Process(); //ctor

	void admitted();
	void schedulerDispatch();
	void eventCompletion();
	void interrupt();
	void eventWait();
	void exit();

	Process* clone() { //for Prototype
		Process* p = new Process();
		return p;
	}

	void pID(int i) {  // for prototype had a hard time with static int
		nextID_ = ++i;
	}


	void report();

	void changeState(State* s) {
		state_ = s;
	}

private:
	State* state_;
	int nextID_ = 0;
	//static int nextID_ = 0;
};


class State {
public:
	virtual void admitted(Process*) {}
	virtual void schedulerDispatch(Process*) {}
	virtual void eventCompletion(Process*) {}
	virtual void interrupt(Process*) {}
	virtual void eventWait(Process*) {}
	virtual void exit(Process*) {}

	virtual void report() = 0;

	void changeState(Process* p, State* s) {
		p->changeState(s);
	}
};



class New : public State {
public:
	static State* instance() {
		static State* onlyInstance = new New();
		return onlyInstance;
	}

	void admitted(Process*) override;

	void report() override { cout << "New"; }

private:
	New() {}
};

class Ready : public State {
public:
	static State* instance() {
		static State* onlyInstance = new Ready();
		return onlyInstance;
	}

	void schedulerDispatch(Process*) override;

	void report() override { cout << "Ready"; }

private:
	Ready() {}
};


class Waiting : public State {
public:
	static State* instance() {
		static State* onlyInstance = new Waiting();
		return onlyInstance;
	}

	void eventCompletion(Process*) override;

	void report() override { cout << "Waiting"; }

private:
	Waiting() {}
};

class Running : public State {
public:
	static State* instance() {
		static State* onlyInstance = new Running();
		return onlyInstance;
	}

	void eventWait(Process*) override;
	void exit(Process*) override;
	void interrupt(Process*) override;

	void report() override { cout << "Running"; }

private:
	Running() {}
};

class Terminated : public State {
public:
	static State* instance() {
		static State* onlyInstance = new Terminated();
		return onlyInstance;
	}


	void report() override { cout << "Terminated"; }

private:
	Terminated() {}
};



#endif 


