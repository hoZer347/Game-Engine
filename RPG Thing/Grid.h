#pragma once

#include "Mesh.h"
#include "Object.h"

namespace grid {
	class Cell :
		public obj::Obj {
	public:
		~Cell();
		void update() {};
		void render() {};

		mesh::Mesh* m = NULL;
	};

	class Grid :
		public obj::Manager<Cell> {
	public:

	private:
	};

	extern Grid* GRID;
};
