#include "Grid.h"

namespace grid {
	Cell::~Cell() {
		delete m;
	};

	Grid* GRID = NULL;
};
