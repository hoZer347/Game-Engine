#pragma once

#include "Camera.h"

#include "glm/glm.hpp"
using namespace glm;

namespace depth {
	class DepthMapper;
	
	extern DepthMapper* create(cam::lightSource* = NULL);
	extern void del(DepthMapper*);
};
