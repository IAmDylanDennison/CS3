#ifndef	SINGLETON_LOGGER
#define SINGLETON_LOGGER

#include <iostream>
#include <fstream>


using std::cout; using std::endl; using std::string;

class logger {
public:
	static logger& instance() {
		static logger s;
		return s;
	}
	void report(const string& s) {
		if (fout_.is_open()) {
			fout_ << s << std::endl;
		}
	}
	~logger() {
		fout_.close();
	}

private:
	logger() {
		fout_.open("test.txt", std::fstream::out | std::fstream::app);
	}
	logger(const logger&);
	logger& operator=(const logger&);
	std::ofstream fout_;  //payload
};


#endif
