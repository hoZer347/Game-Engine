#include "Timer.h"

unsigned int curr_time = (int)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
bool do_timer = true;
