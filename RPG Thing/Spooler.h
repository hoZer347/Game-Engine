#pragma once

#include <vector>
#include <thread>

namespace spooler {
	extern const size_t MAX_CORES;
	extern std::vector<std::thread> threads;

	void close();
};
