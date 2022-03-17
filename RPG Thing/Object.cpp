#include "Object.h"

#include <iostream>

namespace obj {
	std::vector<Obj*> OBJS;
	std::vector<unsigned int> _OBJS;

	Obj::Obj(bool add) {
		if (add) {
			if (_OBJS.empty()) {
				index = OBJS.size();
				OBJS.push_back(this);
			} else {
				index = _OBJS.back();
				OBJS[index] = this;
				_OBJS.pop_back();
			}
		} else index = -1;
	};
	Obj::~Obj() {

	};
	void setup() {
		for (auto& o : OBJS)
			if (o)
				o->setup();
	};
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
