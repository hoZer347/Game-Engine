#pragma once

#include "Mesh.h"
#include "Unit.h"

#include <functional>
#include <set>

class Renderer;

enum {
	U = 0,
	D = 1,
	L = 2,
	R = 3
};

enum {
	TEAM_NULL = 0,
	TEAM_R_MOVE = 1,
	TEAM_G_MOVE = 2,
	TEAM_B_MOVE = 3,
	TEAM_R_ATK = 4,
	TEAM_G_ATK = 5,
	TEAM_B_ATK = 6
};

static double G_BUFFER = .1;
static double G_OPACITY = .3;

// Stores units, and other stuff needed in a map
// Knows neighbours, parent grid
class Cell : public MeshObj<Cell> {
public:
	~Cell();
	void update();
	Cell*& operator[] (unsigned int i) { return next[i]; }
	void change_color(unsigned char i) {
		clr = i;
		for (auto& v : m->vtxs)
			switch (i) {
			case TEAM_NULL:
				v.clr = vec4(1, 1, 1, G_OPACITY);
				break;
			case TEAM_R_MOVE:
				v.clr = vec4(1, .5, .5, G_OPACITY);
				break;
			case TEAM_G_MOVE:
				v.clr = vec4(0, 1, 0, G_OPACITY);
				break;
			case TEAM_B_MOVE:
				v.clr = vec4(0, 0, 1, G_OPACITY);
				break;
			case TEAM_R_ATK:
				v.clr = vec4(1, .5, .5, G_OPACITY);
				break;
			case TEAM_G_ATK:
				v.clr = vec4(.5, 1, .5, G_OPACITY);
				break;
			case TEAM_B_ATK:
				v.clr = vec4(1, 0, 0, G_OPACITY);
				break;
			default:
				break;
			}
	}

	Cell* next[4] = { };
	Unit* u = NULL;

	unsigned char clr = 0;
	double terrain = 1;
};

// 2D array of Cells
class Grid : public MeshObj<Grid> {
public:
	void update();

	Unit* get(unsigned int, unsigned int);

	Cell* hovered = NULL;
	Cell* selected = NULL;
	Renderer* r = NULL;

	bool check_rng(unsigned int, unsigned int);
	std::vector<std::vector<Cell*>> C;
};

extern Grid* GRID;

// Creates a (x, y) - size grid
// f is the function that represents the positions of each cell and their vertices
// animate is whether or not to update each cell
extern void create_grid(
	unsigned int x=10,
	unsigned int y=10,
	bool animate=false);

//
extern void flood_fill(Cell* o, std::set<Cell*>& C, std::function<double(Cell*, Cell*)> f, double i, Cell* c);

//
extern void a_star(Cell* goal, Cell* c, std::vector<Cell*>& path, std::map<Cell*, unsigned short> visited);

//
extern void grid_attach_neighbours();

//
extern bool grid_set(Unit* u, unsigned int x, unsigned int y);

//
extern std::function<double(Cell*, Cell*)> u_ff;

//
extern std::function<void(Vtx&)> y_is_negz;
