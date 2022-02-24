#include "Object.h"

#include <unordered_set>
#include <unordered_map>
#include <stack>

namespace obj {
	std::unordered_set<_Obj*> OBJS;
	int attrib_index=0;
	std::stack<unsigned int> attrib;
	std::unordered_map<const char*, std::unordered_set<void*>> textures;

	_Obj::_Obj() {
		OBJS.insert(this);
	}

	unsigned int new_texture(const char* file_name) {
		return 0;
	}

	unsigned int new_attrib() {
		if (!attrib.empty()) {
			attrib.pop();
			return attrib.top();
		}
		return attrib_index++;
	}

	void rmv(_Obj* o) {
		OBJS.erase(o);
	}

	void del(_Obj* o) {
		o->del();
		OBJS.erase(o);
	}

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
	}
}
