#include "Textures.h"

#include "SOIL/SOIL.h"

#include "GLFW/glew.h"

#include <unordered_map>
#include <string>

namespace texture {
	unsigned int intex=0;
	std::unordered_map<std::string, unsigned int> TEXS;

	unsigned int create(const char* file_name) {
		std::string s = std::string(file_name);

		if (TEXS[s])
			return TEXS[s];

		unsigned int texture = SOIL_load_OGL_texture(
			file_name,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y |
			SOIL_FLAG_NTSC_SAFE_RGB |
			SOIL_FLAG_MULTIPLY_ALPHA);

		TEXS[s] = texture;

		glBindTexture(GL_TEXTURE_2D, texture);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		return texture;
	};
};
