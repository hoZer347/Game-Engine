#pragma once

#include <vector>

namespace obj {
	extern const unsigned char
		STG_RENDER;

	struct Obj {
		Obj();

		virtual void stage(const unsigned char&) { };
	};

	extern std::vector<Obj*> OBJS;
};
