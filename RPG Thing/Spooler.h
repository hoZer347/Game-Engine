#pragma once

#include <chrono>

namespace spooler { // TODO: add comments
	using namespace std::chrono_literals;

	/**/
	enum {
		CONTROL,
		MISC0,
	};

	/**/
	extern const unsigned char MAX_CORES;
	extern	     unsigned char CURR_THREADS;

	/**/
	typedef void(&Task)();
	
	/**/
	extern void push(Task&);

	/**/
	extern bool* push(Task&, double);

	/**/
	extern void close();

	/**/
	enum {
		FIFO,
		LIFO,
		FILO,
		LILO,
	};

	extern void change_order(char c); // TODO: implement this
};
