#pragma once

#include <vector>

namespace obj {
	struct Obj {
		virtual ~Obj() {};
		virtual void update() {};
		virtual void render() {};
		virtual void physics() {};
		virtual void ai() {};
	};

	extern std::vector<Obj*> OBJS;
	extern bool b;

	struct Manager : Obj {

	};

	extern void update();
	extern void render();
};
