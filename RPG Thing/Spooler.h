#pragma once

namespace spooler {
	/**/
	enum {
		CONTROL,
		MISC0,
	};

	/**/
	extern const unsigned char MAX_CORES;
	extern	     unsigned char CURR_THREADS;
	extern				  bool THREAD_BUNDY;

	/**/
	typedef void(&Task)();
	
	/**/
	extern void push(Task&);

	/**/
	extern void push(Task&, double);

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
