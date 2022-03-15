#include "Geo.h"

#include "Mesh.h"
#include "Camera.h"
#include "Shaders.h"
#include "Textures.h"
#include "Lighting.h"

#include "GLFW/glew.h"
#include "GLFW/glfw3.h"

namespace geo {
	namespace square {
		class Square :
			public mesh::Mesh {
		public:
			Square() {
				vtxs = {
					0, 0, 0,
				};

				inds = {
					0,
				};

				add_attrib(3);

				set_shader("Quads_Basic");

				add_texture("Textures/Stone.png");
				add_texture(depth::depth_map);

				drawing_mode = GL_POINTS;
			};
			void render();
		};
		void Square::render() {
			glUseProgram(shader);
			glUniformMatrix4fv(
				glGetUniformLocation(shader, "mvp"),
				1, GL_FALSE, &cam::mvp[0][0]);
			glUniformMatrix4fv(
				glGetUniformLocation(shader, "lightMat"),
				1, GL_FALSE, &depth::lightMat[0][0]);
			glUniformMatrix4fv(
				glGetUniformLocation(shader, "trns"),
				1, GL_FALSE, &trns[0][0]);
			mesh::Mesh::render();
		};



		Square* create() {
			Square* f = new Square();

			return f;
		};
		void del(Square* f) {
			delete f;
		};
	};
};
