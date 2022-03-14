#include "Lighting.h"

#include "Object.h"
#include "Mesh.h"
#include "Window.h"
#include "Geo.h"
#include "Shaders.h"
#include "Camera.h"

#include "GLFW/glew.h"

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
using namespace glm;

#include <iostream>

/*

Shadow Effect Pipeline:
- Make a new framebuffer for depth
	- Assign it to a texture output
	- Draw all objects onto texture

- Somehow add texture to the main frame
*/

namespace lighting {
	class Lighting :
		public obj::Obj {
	public:
		void setup();
		void update();
		void render();
		 
	private:
		mesh::Mesh* m = (mesh::Mesh*)geo::square::create();

		unsigned int
			depth_map=0,
			depth_fbo=0,
			shader=0;

		mat4
			proj = mat4(1),
			view = mat4(1),
			vp   = mat4(1);
	};

	Lighting* l = NULL;



	void Lighting::setup() {
		glGenFramebuffers(1, &depth_fbo);
		glGenTextures(1, &depth_map);

		shader = shader::create("Depth_Basic");

		int w, h;
		glfwGetWindowSize(WINDOW, &w, &h);

		glBindTexture(GL_TEXTURE_2D, depth_map);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, w, h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			glBindFramebuffer(GL_FRAMEBUFFER, depth_fbo);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_map, 0);
				glDrawBuffer(GL_NONE);
				glReadBuffer(GL_NONE);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		m->set_shader(shader);
		m->texs[0] = depth_map;

		proj = perspective(radians(45.f), (float)w / (float)h, .1f, 100.f);
		view = lookAt(vec3(0, 0, 0), vec3(0, 0, -2), vec3(0, 1, 0));
		vp = proj * view;

		glUniformMatrix4fv(glGetUniformLocation(shader, "light"), 1, GL_FALSE, &vp[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shader, "mode"), 1, GL_FALSE, &cam::mode[0][0]);
	};
	void Lighting::update() {
		int w, h;
		glfwGetWindowSize(WINDOW, &w, &h);

		glBindFramebuffer(GL_FRAMEBUFFER, depth_fbo);

		glViewport(0, 0, w, h);
		glClear(GL_DEPTH_BUFFER_BIT);

		obj::render();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	};
	void Lighting::render() {

	};

	void create() {
		l = new Lighting();
	};

};
