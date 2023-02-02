#include "Spooler.h"

#include <vector>

namespace spooler {
	const size_t MAX_CORES = std::thread::hardware_concurrency();
};
