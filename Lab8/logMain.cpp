#include "Logger.hpp"



int main() {
	logger::instance().report("One");
	logger::instance().report("Two");
	logger::instance().report("Three");
	logger::instance().report("Ten");
	logger::instance().report("nice");
}
