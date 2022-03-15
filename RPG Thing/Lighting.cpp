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

namespace depth {
	unsigned int
		depth_map=0;

	mat4 lightMat;

	class DepthMapper :
		public obj::Obj {
	public:
		DepthMapper();
		~DepthMapper() {
			geo::square::del((geo::square::Square*)m);
			glDeleteBuffers(1, &depth_fbo);
			glDeleteTextures(1, &depth_map);
		};
 		void setup();
		void update();
		void render();
		 
	private:
		mesh::Mesh* m = (mesh::Mesh*)geo::square::create();

		unsigned int
			depth_fbo=0,
			x_size=1024,
			y_size=1024;

		mat4
			mode = mat4(1),
			proj = mat4(1),
			view = mat4(1),
			mvp  = mat4(1);
	};

	DepthMapper* l = NULL;

	DepthMapper::DepthMapper() {
		glGenFramebuffers(1, &depth_fbo);
		glGenTextures(1, &depth_map);

		glBindTexture(GL_TEXTURE_2D, depth_map);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, x_size, y_size, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glBindFramebuffer(GL_FRAMEBUFFER, depth_fbo);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_map, 0);
				glDrawBuffer(GL_NONE);
				glReadBuffer(GL_NONE);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		m->texs[0] = depth_map;

		mode = rotate(90.f, vec3(1, 0, 0)) * translate(vec3(0, -2, 0));
		proj = perspective(radians(90.f), (float)x_size / (float)y_size, .1f, 100.f);
		view = lookAt(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0));
	};
	void DepthMapper::setup() {

	};
	void DepthMapper::update() {
		glBindFramebuffer(GL_FRAMEBUFFER, depth_fbo);

		glViewport(0, 0, x_size, y_size);
		glClear(GL_DEPTH_BUFFER_BIT);

		mat4 m1, m2, m3, m4;

		mvp = proj * view * mode;

		m1 = cam::mode;
		m2 = cam::view;
		m3 = cam::proj;
		m4 = cam::mvp;

		cam::mode = mode;
		cam::view = view;
		cam::proj = proj;
		cam::mvp  = mvp;

		lightMat = mvp;

		obj::render();

		cam::mode = m1;
		cam::view = m2;
		cam::proj = m3;
		cam::mvp  = m4;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	};
	void DepthMapper::render() {

	};

	void create() {
		l = new DepthMapper();
	};

	void close() {
		delete l;
	};
};
