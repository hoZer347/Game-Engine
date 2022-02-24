#pragma once

#include "Mesh.h"

namespace sprite {
	class Sprite : public
		mesh::Mesh,
		mesh::Quads {
	public:
		void bind_texture(const char*);
		void setup();
		void update();

	private:
		unsigned int texture=0;
	};
}
