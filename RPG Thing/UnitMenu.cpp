#include "UnitMenu.h"

void UnitOption::on() {
	if (on_off) return; on_off = true;

	std::cout << "Test" << std::endl;

	for (auto& i : t->m->vtxs)
		i.clr = vec4(0, 0, 0, 1);
}

void UnitOption::off() {
	if (!on_off) return; on_off = false;

	std::cout << "Test3" << std::endl;

	for (auto& i : t->m->vtxs)
		i.clr = vec4(0, 0, 0, .5);
}

bool UnitOption::intersect() {
	vec3 v;
	if (
		intersectRayTriangle(
			inputs->mouse_ray[CAM_EYE], inputs->mouse_ray[CAM_RAY],
			t->pos(0), t->pos(1), t->pos(2), v
		) ||
		intersectRayTriangle(
			inputs->mouse_ray[CAM_EYE], inputs->mouse_ray[CAM_RAY],
			t->pos(0), t->pos(2), t->pos(3), v
		))	return true;
	else	return false;
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
