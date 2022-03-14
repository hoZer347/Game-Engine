#include "Geo.h"

#include "Mesh.h"

#include "GLFW/glew.h"
#include "GLFW/glfw3.h"

#include "Camera.h"
#include "Shaders.h"
#include "Textures.h"

namespace geo {
	namespace square {
		class Square :
			public mesh::Mesh {
		public:
			Square() {
				vtxs = {
					0, 0, 0, 0, 0,
					1, 0, 0, 1, 0,
					1, 1, 0, 1, 1,
					0, 1, 0, 0, 1,
				};

				inds = {
					0, 1, 2, 3
				};

				add_attrib(3);
				add_attrib(2);

				set_shader("Faces_Basic");

				add_texture("Textures/Stone.png");

				drawing_mode = GL_QUADS;
			};
			void render();
		};
		void Square::render() {
			glUseProgram(shader);
			mat4 m = cam::mvp * trns;
			glUniformMatrix4fv(
				glGetUniformLocation(shader, "trns"),
				1, GL_FALSE, &m[0][0]);
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
