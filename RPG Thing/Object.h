#pragma once

#include <vector>

namespace obj {
	struct Obj {
		virtual void stage(size_t&)=0;
	};

	extern std::vector<Obj*> OBJS;
};
