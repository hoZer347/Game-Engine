#include "Object.h"

#include <iostream>

namespace obj {
	std::vector<Obj*> OBJS;
	std::vector<unsigned int> _OBJS;

	void update() {
		for (auto& o : OBJS)
			if (o)
				o->update();
	};
	void render() {
		for (auto& o : OBJS)
			if (o)
				o->render();
	};
	void add(Obj* o) {
		if (_OBJS.empty()) {
			o->index = OBJS.size();
			OBJS.push_back(o);
		} else {
			o->index = _OBJS.back();
			OBJS[o->index] = o;
			_OBJS.pop_back();
		}
	};
	void rmv(Obj* o) {
		OBJS[o->index] = NULL;
	};
	void close() {
		while (!OBJS.empty()) {
			Obj* o = OBJS.back();
			delete o;
			OBJS.pop_back();
		};
	};
}
