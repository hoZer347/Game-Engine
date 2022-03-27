#include "Geo.h"

#include "Mesh.h"
#include "Camera.h"
#include "Shaders.h"
#include "Textures.h"

#include "GLFW/glew.h"
#include "GLFW/glfw3.h"

#include <vector>

namespace geo {
	class Geo : 
		public mesh::Mesh {
	public:
		Geo();
		void setup();
		void update();
		void render();

	private:
		unsigned int
			_mvp=0,
			_trns=0;
	};

	class GeoManager :
		public obj::Manager<Geo> {
		
	};

	GeoManager GEO;



	Geo::Geo() {
		vtxs = { 0, 0, 0, };
		inds = { 0, };

		add_attrib(3);
		drawing_mode = GL_POINTS;
	}
	void Geo::setup() {
		glUseProgram(shader);
		_mvp = glGetUniformLocation(shader, "mvp");
		_trns = glGetUniformLocation(shader, "trns");

		Mesh::setup();
	};
	void Geo::update() {
		glUseProgram(shader);
		Mesh::update();
	};
	void Geo::render() {
		glUseProgram(shader);
		glUniformMatrix4fv(_mvp, 1, GL_FALSE, &cam::mvp[0][0]);
		glUniformMatrix4fv(_trns, 1, GL_FALSE, &trns[0][0]);
		mesh::Mesh::render();
	};

	namespace square {
		Geo* create() {
			Geo* g = GEO.create();

			g->set_shader(
				"Position_Basic.vert",
				"Quads_Basic.geom",
				"Texture_Basic.frag");

			g->setup();

			return g;
		};
	};

	namespace cube {
		Geo* create() {
			Geo* g = GEO.create();

			g->set_shader(
				"Position_Basic.vert",
				"Cubes_Basic.geom",
				"Texture_Basic.frag");

			g->setup();

			return g;
		};
	};

	void add_texture(Geo* g, const char* f) {
		g->add_texture(f);
	};
};
