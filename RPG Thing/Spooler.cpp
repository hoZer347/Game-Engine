#include "Spooler.h"

#include <stdio.h>
#include <time.h>
#include <future>
#include <thread>
#include <queue>

#include <iostream>

namespace spooler {
	/**/
	const unsigned char	MAX_CORES	 = std::thread::hardware_concurrency();
		  unsigned char	CURR_THREADS = 0;
				   bool	THREAD_BUNDY = true;
	;

	/**/
	std::queue<std::thread*> threads;
	
	void init() {

	};

	void push(Task& t) {
		threads.push(new std::thread(t));
		threads.back()->detach();
	};

	void push(Task& t, double interval) {
		threads.push(new std::thread([t, interval]() {
			std::clock_t
				c1 = std::clock(),
				c2 = std::clock();

			while (THREAD_BUNDY) {
				c1 = c2;

				while ((double)(c2 - c1) < interval)
					c2 = std::clock();

				t();
			};
			}));
		threads.back()->detach();
	};

	void close() {
		THREAD_BUNDY = false;
	};
};
