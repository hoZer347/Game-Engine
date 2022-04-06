#include "Object.h"

#include <vector>

namespace obj {
	bool b = false;
	std::vector<Obj*> OBJS;

	void update() {
		while (!b) {}

		for (auto& o : OBJS)
			o->update();
	};

	void render() {
		while (!b) {}

		
	};
};
