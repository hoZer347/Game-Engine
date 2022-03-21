#include "Perspective.h"

#include "Mesh.h"
#include "Object.h"
#include "Shaders.h"
#include "Geo.h"

#include "GLFW/glew.h"

namespace perspective {
	class _Perspective :
		Perspective {
	public:
		_Perspective() {
			glGenBuffers(1, &fbo);
			glGenBuffers(1, &ubo);
			glGenTextures(1, &texture);
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
		_Perspective,
		public obj::Obj {
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
		_Perspective,
		public obj::Obj {
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
