#pragma once

#define _CRTDBG_MAP_ALLOC

namespace shader {
	extern unsigned int create(const char*);
	extern unsigned int create(const char*, const char*);
	extern unsigned int create(const char*, const char*, const char*);
};
