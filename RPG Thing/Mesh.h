#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include "Object.h"
using namespace obj;

#include <vector>

namespace mesh {
	class Mesh : public Obj {
	public:
		void add_attrib(unsigned char size);
		void pump(std::vector<float>&);
		void pump(std::vector<unsigned int>&);
		void setup();
		void update();
		void render();

	protected:
		unsigned int
			_vtxs=0,
			_inds=0,
			stride=0,
			drawing_mode=0;

		std::vector<float> vtxs;
		std::vector<unsigned int> inds;
		std::vector<std::pair<unsigned int, unsigned int>> atbs;
	};


	
	class Shader :
		public Mesh {
	public:
		~Shader();
		void set_shader(const char*);
		void setup();
		void render();

	protected:
		unsigned int
			shader=0;
		const char*
			shader_name = "";
	};



	class Texture :
		public Shader {
	public:
		~Texture();
		void set_texture(const char*);
		void setup();
		void render();

	protected:
		unsigned int
			texture=0;
		const char*
			texture_name = "";
	};



	class Transform :
		public Mesh {
	public:
		vec4 pos(unsigned int=0);

		mat4 trns;
	};
}
