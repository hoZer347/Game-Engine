#include "Perspective.h"

#include "Mesh.h"
#include "Object.h"
#include "Shaders.h"
#include "Geo.h"

#include "GLFW/glew.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
using namespace glm;

namespace perspective {
	class _Perspective :
		public mesh::Mesh,
		Perspective {
	public:
		_Perspective() {
			glGenBuffers(1, &fbo);
			glGenBuffers(1, &ubo);
			glGenTextures(1, &texture);

			m.vtxs = { 0, 0, 0 };
			m.inds = { 0 };
			m.add_attrib(3);
			m.drawing_mode = GL_POINTS;
			m.set_shader(
				"Position_Basic.vert",
				"Quads_Basic.geom",
				"Texture_Basic.frag"
			);
			m.setup();
		};
		~_Perspective() {
			glDeleteBuffers(1, &fbo);
			glDeleteBuffers(1, &ubo);
			glDeleteTextures(1, &texture);
		};
		void update();
		void render();

	protected:
		int
			x_size=0,
			y_size=0;

		Mesh m;

		unsigned int
			fbo=0, ubo=0,
			texture=0,
			shader=0;
	};
	void _Perspective::update() {

	};
	void _Perspective::render() {
		
	};

	void load(Perspective* p) {

	};

	class Camera :
		_Perspective {
	public:
		Camera();
		~Camera();
		void update();
		void render();

	private:

	};
	class CameraManager :
		public obj::Manager<Camera> { };
	CameraManager CAMERA;
	Camera::Camera() {
		this->_Perspective::_Perspective();

		glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x_size, y_size, 0, GL_RGBA, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo, 0);
				glDrawBuffer(GL_NONE);
				glReadBuffer(GL_NONE);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	};
	Camera::~Camera() {
		this->_Perspective::~_Perspective();
	};
	void Camera::update() {

	};
	void Camera::render() {
		
	};

	namespace camera {
		Perspective* create() {
			Camera* l = CAMERA.create();

			return (Perspective*)l;
		};

		void del(Perspective* p) {
			CAMERA.del((Camera*)p);
		};
	};

	class Light :
		_Perspective {
	public:
		Light();
		~Light();
		void update();
		void render();

	private:

	};
	class LightManager :
		public obj::Manager<Light> { };
	LightManager LIGHTS;
	Light::Light() {
		this->_Perspective::_Perspective();


	};
	Light::~Light() {
		this->_Perspective::~_Perspective();
	};
	void Light::update() {

	};
	void Light::render() {

	};

	namespace light {
		Perspective* create() {
			Light* l = LIGHTS.create();

			return (Perspective*)l;
		};
		void del(Perspective* p) {
			LIGHTS.del((Light*)p);
		};
	};
};
