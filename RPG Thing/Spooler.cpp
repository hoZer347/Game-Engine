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
	std::vector<std::thread*> threads;

	void push(Task& t) {
		threads.push_back(new std::thread(t));
		threads.back()->detach();
	};

	bool* push(Task& t, double interval) {
		bool* flag = new bool();
		*flag = true;

		threads.push_back(new std::thread([t, interval, flag]() {
			std::clock_t
				c1 = std::clock(),
				c2 = std::clock();

			while (THREAD_BUNDY && flag) {
				c1 = c2;

				while ((double)(c2 - c1) < interval) {
					c2 = std::clock();
				}

				t();
			};
			}));
		threads.back()->detach();

		return flag;
	};

	void close() {
		THREAD_BUNDY = false;
		
		while (threads.size())
			if (threads.back()->joinable())
				threads.pop_back();
	};
};
