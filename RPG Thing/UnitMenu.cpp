#include "UnitMenu.h"

void UnitOption::on() {
	if (on_off) return; on_off = true;

	for (auto& i : t->letters) {
		Letter* l = t->f->letters[i.first];
		l->m->vtxs[i.second + 0].clr = vec4(1, 1, 1, 1);
		l->m->vtxs[i.second + 1].clr = vec4(1, 1, 1, 1);
		l->m->vtxs[i.second + 2].clr = vec4(1, 1, 1, 1);
		l->m->vtxs[i.second + 3].clr = vec4(1, 1, 1, 1);
	}
}

void UnitOption::off() {
	if (!on_off) return; on_off = false;

	for (auto& i : t->letters) {
		Letter* l = t->f->letters[i.first];
		l->m->vtxs[i.second + 0].clr = vec4(1, 1, 1, .5);
		l->m->vtxs[i.second + 1].clr = vec4(1, 1, 1, .5);
		l->m->vtxs[i.second + 2].clr = vec4(1, 1, 1, .5);
		l->m->vtxs[i.second + 3].clr = vec4(1, 1, 1, .5);
	}
}

bool UnitOption::intersect() {
	vec3 v1 = t->get_v(BOTTOM_LEFT), v2 = t->get_v(TOP_RIGHT);

	int w, h;
	glfwGetWindowSize(inputs->window, &w, &h);

	double x = 2*(inputs->mx / w)-1;
	double y = 2*(inputs->my / h)-1;

	if (v1.x < x && x < v2.x &&
		v1.y < y && y < v2.y)
		return true;
	else
		return false;
}

void UnitMenu::add(const char* name, std::function<void(Unit*)> f) {
	Text* t = create_text(name, font);
	UnitOption* u = new UnitOption();
	u->t = t;
	u->f = f;

	translate(t, vec3(-1, 1, 0));

	O.push_back(u);
}

void UnitMenu::unload() {
	clear();
}
