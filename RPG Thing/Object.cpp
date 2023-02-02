#include "Object.h"

namespace obj {
	const unsigned char
		STG_RENDER=1;
	
	Obj::Obj() { OBJS.push_back(this); };

	std::vector<Obj*> OBJS;
};
