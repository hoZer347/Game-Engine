#include "Object.h"

#include "GLFW/glew.h"

#include <unordered_set>
#include <unordered_map>
#include <tuple>
#include <string>
#include <stack>

#include <SOIL/SOIL.h>
#define STB_IMAGE_IMPLEMENTATION

namespace obj {
	std::unordered_set<_Obj*> OBJS;
	int attrib_index=0;
	std::stack<unsigned int> attrib;
	std::unordered_map<std::string, std::tuple<unsigned int, std::unordered_set<void*>>> textures;

	_Obj::_Obj() {
		OBJS.insert(this);
	}

	unsigned int new_texture(std::string file_name, void* v) {
		GLuint texture=0;
		auto& i = textures[file_name];
		std::unordered_set<void*> S;

		if (S.empty()) {
			texture = SOIL_load_OGL_texture(
				file_name.c_str(),
				SOIL_LOAD_AUTO,
				SOIL_CREATE_NEW_ID,
				SOIL_FLAG_INVERT_Y |
					SOIL_FLAG_NTSC_SAFE_RGB |
					SOIL_FLAG_MULTIPLY_ALPHA);

			glBindTexture(GL_TEXTURE_2D, texture);
			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		S.insert(v);
		return std::get<0>(i);
	}
	unsigned int new_texture(const char* file_name, void* v) { return new_texture(std::string(file_name), v); }

	void del_texture(const char* file_name) {

	}

	unsigned int new_attrib() {
		if (!attrib.empty()) {
			attrib.pop();
			return attrib.top();
		}
		return attrib_index++;
	}

	void del_attrib(unsigned int) {

	}

	void rmv(_Obj* o) {
		OBJS.erase(o);
	}

	void del(_Obj* o) {
		o->del();
		OBJS.erase(o);
	}

	void setup() {
		for (auto& o : OBJS)
			o->setup();
	}

	void update() {
		for (auto& o : OBJS)
			o->update();
	}

	void render() {
		for (auto& o : OBJS)
			o->render();
	}

	void clear() {
		for (auto& o : OBJS)
			o->del();

		OBJS.clear();
	}
}
