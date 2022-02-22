#include "UnitMenu.h"
#include "UnitMenuActions.h"

#include "Text.h"

void create_unit_menu(std::vector<unsigned short>& options) {
	new_menu<UnitMenu>();

	((UnitMenu*)MENU)->font = create_font();

	make_meshobj((UnitMenu*)MENU);

	for (auto& o : options) {

	}

	MENU->add("Attack", attack);
	MENU->add("Cancel", cancel);
	MENU->add("Wait", wait);

	inputs->m[GLFW_MOUSE_BUTTON_LEFT] = [](int a, int m) {
		if (a == GLFW_PRESS)
			MENU->select();
	};

	inputs->m[GLFW_MOUSE_BUTTON_RIGHT] = [](int a, int m) {
		if (a == GLFW_PRESS)
			cancel();
	};
}

void UnitOption::on() {
	if (on_off) return; on_off = true;

	for (auto& i : t->m->vtxs)
		i.clr = vec4(0, 0, 0, 1);
}

void UnitOption::off() {
	if (!on_off) return; on_off = false;

	for (auto& i : t->m->vtxs)
		i.clr = vec4(0, 0, 0, .5);
}

bool UnitOption::intersect() {
	vec3 v;
	if (
		intersectRayTriangle(
			inputs->mouse_ray[CAM_EYE],
			inputs->mouse_ray[CAM_RAY],
			t->pos(0), t->pos(1), t->pos(2), v
		) ||
		intersectRayTriangle(
			inputs->mouse_ray[CAM_EYE],
			inputs->mouse_ray[CAM_RAY],
			t->pos(0), t->pos(2), t->pos(3), v
		))	return true;
	else	return false;
}

void UnitMenu::add(const char* name, std::function<void()> f) {
	UnitOption* u = new UnitOption();
	u->t = create_text(name, font);
	u->f = f;

	if (!O.empty()) {
		UnitOption* o = (UnitOption*)O.back();

		u->t->m->trns = translate(
			u->t->m->trns,
			o->t->pos(0) - vec3(0, o->t->max.y, 0)
		);
	}

	O.push_back(u);
}

void UnitMenu::unload() {
	for (auto& o : O)
		delete_text(((UnitOption*)o)->t);

	delete_meshobj(this);
}

void UnitMenu::change_focus(bool on_off) {
	animate = on_off;

	for (auto& o : O)
		((UnitOption*)o)->t->m->show = on_off;
}
