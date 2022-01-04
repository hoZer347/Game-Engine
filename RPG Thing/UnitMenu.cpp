#include "UnitMenu.h"

void UnitOption::on() {
	if (!on_off) return; on_off = true;

	for (auto& i : t->m->vtxs)
		i.clr = vec4(0, 0, 0, 1);
}

void UnitOption::off() {
	if (on_off) return; on_off = false;

	for (auto& i : t->m->vtxs)
		i.clr = vec4(0, 0, 0, .5);
}

bool UnitOption::intersect() {
	vec3 v;
	if (
		intersectRayTriangle(
			inputs->mouse_ray[0], inputs->mouse_ray[1],
			t->m->pos(0), t->m->pos(1), t->m->pos(2), v
		) ||
		intersectRayTriangle(
			inputs->mouse_ray[0], inputs->mouse_ray[1],
			t->m->pos(0), t->m->pos(3), t->m->pos(2), v
		)) {

		on();
		return true;
	}

	else return false;
}

void UnitMenu::add(const char* name, std::function<void(Unit*)> f) {
	UnitOption* u = new UnitOption();
	u->t = create_text(name, font);
	u->f = f;

	O.push_back(u);
}

void UnitMenu::unload() {
	inputs->prev();

	delete_meshobj(this);
}
