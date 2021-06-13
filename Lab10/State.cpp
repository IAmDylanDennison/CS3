#include "State.hpp"


Process::Process() {
	state_ = New::instance();
}

void Process::admitted() {
	state_->admitted(this);
}


void Process::schedulerDispatch() {
	state_->schedulerDispatch(this);
}


void Process::eventCompletion() {
	state_->eventCompletion(this);
}

void Process::interrupt() {
	state_->interrupt(this);
}

void Process::eventWait() {
	state_->eventWait(this);
}

void Process::exit() {
	state_->exit(this);
}

void Process::report() {

	cout << "Process " << nextID_ << " is ";  state_->report(); cout << std::endl;
	cout << endl;
}

//processes of the states

void New::admitted(Process *p) {
	changeState(p, Ready::instance());
}

void Ready::schedulerDispatch(Process* p) {
	changeState(p, Running::instance());
}

void Waiting::eventCompletion(Process* p) {
	changeState(p, Ready::instance());
}

void Running::eventWait(Process* p) {
	changeState(p, Waiting::instance());
}

void Running::interrupt(Process* p) {
	changeState(p, Ready::instance());
}

void Running::exit(Process* p) {
	changeState(p, Terminated::instance());
}
