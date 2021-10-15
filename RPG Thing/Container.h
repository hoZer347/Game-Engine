#pragma once

#include "Renderer.h"

struct Object {

};

class Place {
public:
	friend class Container;

	operator Object*() const { return o; }
	Object* o = NULL;
};

class Container {
public:
	auto begin() { return objs.begin(); }
	auto end()	 { return objs.end();	}
	Object* operator[](int i) { if (i < objs.size()) return objs[i]; }

private:
	std::vector<Object*> objs;
};
