#include "Camera.h"

#include "Window.h"
#include "Object.h"

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
using namespace glm;

namespace cam {
	mat4
		trns = mat4(1),
		rotn = mat4(1),
		roll = mat4(1),
		ptch = mat4(1),
		yaww = mat4(1),
		mode = mat4(1),
		view = mat4(1),
		proj = mat4(1),
		mvp  = mat4(1);

	class Cam :
		public obj::Obj{
	public:
		void setup() {

		};
		void update() {
			int w, h;
			glfwGetWindowSize(WINDOW, &w, &h);

			rotn = roll * ptch * yaww;
			mode = rotn * trns;
			view = lookAt(
				vec3(0, 0, 0),
				vec3(0, 0, -1),
				vec3(0, 1, 0));
			proj = perspective(radians(90.f), (float)w / (float)h, .1f, 1000.f);
			mvp = proj * view * mode;
		};
		void render() {

		};
	};

	Cam* cam = NULL;

	void update() {
		cam->update();
	};

	void create() {
		cam = new Cam();
	};

	void close() {
		delete cam;
	};
};
