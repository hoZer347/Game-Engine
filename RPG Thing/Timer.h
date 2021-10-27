#pragma once

#include <chrono>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

extern int curr_time;

static void update_timer() {
	curr_time = (int)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
};
