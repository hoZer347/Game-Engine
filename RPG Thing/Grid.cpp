#include "Grid.h"

Grid::Grid(int x, int y) {
	std::vector <Cell*> temp;

	for (int i = 0; i < x; i++) {
		temp.clear();

		for (int j = 0; j < y; j++)
			temp.push_back(new Cell(i, j));

		grid.push_back(temp);
	}
}

Cell* Cell::operator[](int i) {
	switch (i) {
	case U:
		return _u;
	case D:
		return _d;
	case L:
		return _l;
	case R:
		return _r;
	default:
		return NULL;
	}
}
