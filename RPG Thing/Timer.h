#pragma once

#include <functional>
#include <chrono>
#include <thread>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

extern unsigned int curr_time;
extern bool do_timer;

static void clock_tick() {
	while (do_timer)
		curr_time = (int)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

static auto start_clock() {
	std::thread clock (clock_tick);

	return clock;
}

static void stop_clock() {
	do_timer = false;
}
