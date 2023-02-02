#include "Unit.h"

#include "Sprite.h"

Unit* create_unit() {
	Unit* u = new Unit();

	u->m = create_square();
	u->m->add(create_square(false));

	// Setting the healthbar
	auto i = u->m->vtxs.begin();
	for (; i < u->m->vtxs.begin() + 4; i++)
		i->clr = vec4(0, 1, 0, 1);	// Setting Green
	for (; i != u->m->vtxs.end(); i++)
		i->clr = vec4(1, 0, 0, 1);	// Setting Red
	for (auto& i : u->m->vtxs) {
		i.pos *= .8;				// Setting Positions
		i.pos.y /= 16;
		i.pos += vec3(.1, .1, .2);
	}
	std::reverse(u->m->inds.begin()+4, u->m->inds.end());
	//

	return u;
}

void Unit::update() {
	m->trns = s->m->trns;
}

std::vector<unsigned short>& Unit::get_options() {
	return options;
}

std::vector<unsigned short>& Unit::get_skills() {
	return skills;
}
