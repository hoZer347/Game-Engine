#include "Depth.h"

#include "Mesh.h"
#include "Window.h"
#include "Geo.h"
#include "Shaders.h"
#include "Camera.h"

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
using namespace glm;

#include <iostream>

namespace depth {
	class DepthMapper :
		public mesh::Mesh {
	public:
		DepthMapper();
		~DepthMapper() {
			glDeleteBuffers(1, &depth_fbo);
			glDeleteTextures(1, &depth_map);
		};
		void bind();
		void bind(cam::lightSource*);
 		void setup();
		void update();
		void render();
		
	private:
		unsigned int
			depth_fbo=0,
			depth_map=0,
			x_size=1024,
			y_size=1024;

		mat4
			&mode = cam::mode,
			&proj = cam::view,
			&view = cam::proj,
			&mvp  = cam::mvp;
	};

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

		vtxs = {
			0, 0, 0,
		};

		inds = {
			0,
		};

		set_shader(
			"Position_Basic.vert",
			"Quads_Basic.geom",
			"Texture_Basic.frag");

		add_texture(depth_map);

		add_attrib(3);

		drawing_mode = GL_POINTS;

		opaque = false;
	};
	void DepthMapper::bind() {
		mode = cam::mode,
		proj = cam::view,
		view = cam::proj,
		mvp  = cam::mvp;
	};
	void DepthMapper::bind(cam::lightSource* l) {
		mode = l->mode,
		proj = l->view,
		view = l->proj,
		mvp  = l->mvp;
	};
	void DepthMapper::setup() {
		glUseProgram(shader);

		Mesh::setup();
	};
	void DepthMapper::update() {
		Mesh::update();

		glBindFramebuffer(GL_FRAMEBUFFER, depth_fbo);

		glViewport(0, 0, x_size, y_size);
		glClear(GL_DEPTH_BUFFER_BIT);

		mat4 m = cam::mvp;

		cam::mvp = mvp;

		for (auto& m : mesh::MESH)
			if (m->opaque)
				m->render();

		cam::mvp = m;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	};
	void DepthMapper::render() {
		glUseProgram(shader);
		mat4 m = mat4(1);

		glUniformMatrix4fv(
			glGetUniformLocation(shader, "mvp"),
			1, GL_FALSE, &m[0][0]);
		glUniformMatrix4fv(
			glGetUniformLocation(shader, "trns"),
			1, GL_FALSE, &m[0][0]);

		Mesh::render();
	};

	DepthMapper* create(cam::lightSource* l) {
		DepthMapper* d = new DepthMapper();

		if (l)
			d->bind(l);

		return d;
	};
	void del(DepthMapper* d) {
		delete d;
	};
};
