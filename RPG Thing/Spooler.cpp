#include "Spooler.h"

namespace spooler {
	const size_t MAX_CORES = std::thread::hardware_concurrency();
	std::vector<std::thread> threads;

	void close() {
		for (auto& t : threads)
			t.join();
	};
};
