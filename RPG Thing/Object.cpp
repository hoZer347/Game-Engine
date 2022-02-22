#include "Object.h"

namespace Object {
	std::unordered_set<_Obj*> OBJS;

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
	};

	void add(_Obj* o) {
		OBJS.insert(o);
	}

	void del(_Obj* o) {
		o->del();
		OBJS.erase(o);
		delete o;
	}
}
