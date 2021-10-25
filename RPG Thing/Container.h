#pragma once

#include <vector>

struct Object { };

class Place {
public:
	Object* o = NULL;
};

class Container {
public:
	void update() { }
	auto begin() { return objs.begin(); }
	auto end()	 { return objs.end();	}
	Object* operator[](size_t i) { if (i < objs.size()) return objs[i]->o; }

private:
	std::vector<Place*> objs;
};
