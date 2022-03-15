#include "Grid.h"

#include "Mesh.h"

#include <vector>

namespace grid {
	struct Cell {

	};

	class Grid :
		public obj::Obj {
	public:
		void setup();
		void update();
		void render();

	private:

	};

	std::vector<std::vector<Cell*>> cells;



	Cell* at(unsigned int x, unsigned int y) {
		return NULL;
	};
};
