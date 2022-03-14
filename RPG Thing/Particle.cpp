#include "Particle.h"

#include "Mesh.h"

#include "GLFW/glew.h"
#include "GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

namespace particle {
	enum {
		SHATTER_SPRITE,
		SHATTER_TERRAIN,
	};

	class Particle :
		public mesh::Mesh {
	public:
		Particle();
		~Particle();
		void setup();
		void update();
		void render();

	private:
		std::vector<unsigned int> texs;
	};

	Particle::Particle() {
		drawing_mode = GL_TRIANGLES;
	};
	Particle::~Particle() {

	};
	void Particle::setup() {
		Mesh::setup();
	};
	void Particle::update() {
		Mesh::update();
	};
	void Particle::render() {
		Mesh::render();
	};



	class ParticleManager :
		public Manager<Particle> {
	public:
		void update();
	private:
	};

	ParticleManager PARTICLE;

	void ParticleManager::update() {
		
	};



	void shatter(sprite::Sprite* s) {
		Particle* p = PARTICLE.create();

		p->add_attrib(3);
		
		sprite::del(s);


	};
};
