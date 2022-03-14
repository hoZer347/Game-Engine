#include "Object.h"

#include <iostream>

namespace obj {
	std::unordered_set<Obj*> OBJS;

	Obj::Obj(bool add) {
		if (add)
			OBJS.insert(this);
	};
	Obj::~Obj() {
		OBJS.erase(this);
	};
	void setup() {
		for (auto& o : OBJS)
			o->setup();
	};
	void update() {
		for (auto& o : OBJS)
			o->update();
	};
	void render() {
		for (auto& o : OBJS)
			o->render();
	};
	void rmv(Obj* o) {
		OBJS.erase(o);
	};
	void close() {
		for (auto& o : OBJS)
			delete o;
	}
}
