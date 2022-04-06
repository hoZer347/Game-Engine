#pragma once

#include "Object.h"

#include <stack>

namespace stage {
	struct Stage {
		std::stack<obj::Obj*> objs;
		Stage* next = this;
	};

	extern Stage* create();
};
