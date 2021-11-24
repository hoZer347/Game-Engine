#include "Timer.h"

int curr_time = (int)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
int ticks = 0;
