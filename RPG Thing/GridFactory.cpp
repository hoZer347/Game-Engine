#include "GridFactory.h"

#include "Grid.h"

#include "GLFW/glew.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

enum {

};

namespace grid {
	void test_grid() {
		if (GRID) delete GRID;

		GRID = new Grid();

		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++) {
				Cell* c = GRID->create();

				c->m = new mesh::Mesh();
				c->m->vtxs = { 0, 0, 0 };
				c->m->inds = { 0 };
				c->m->add_attrib(3);
				c->m->drawing_mode = GL_POINTS;
				c->m->set_shader(
					"Position_Basic.vert",
					"Quads_Basic.geom",
					"Texture_Basic.frag"
				);
				c->m->trns =
					translate(vec3(i, 0, j)) *
					rotate(45.f, vec3(1, 0, 0));
				c->m->add_texture("Stone.png");
				c->m->setup();
				obj::add(c->m);
			}
	};

	void load(unsigned int i) {
		switch (i) {
		case 0:
			test_grid();
			break;
		case 1:
			break;
		case 2:
			break;
		default:
			break;
		};
	};

	void close() {
		delete GRID;
	};
};
