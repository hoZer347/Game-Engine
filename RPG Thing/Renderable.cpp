#include "Renderable.h"

// Flips the tris / texs of a given object
static void r_flip(Tri* tri) {
	vec3 p = tri->v1->pos;
	tri->v1->pos = tri->v3->pos;
	tri->v3->pos = p;
}
