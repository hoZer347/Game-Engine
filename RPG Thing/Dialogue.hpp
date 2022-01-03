#include "Dialogue.h"

// Sets up inputs and data for a dialogue
static void init_dialogue(Dialogue* d) {

	// Setting text box
	d->m = create_square();

	d->m->vtxs[0].pos = vec3(-0.9, -0.9, -0.001);
	d->m->vtxs[1].pos = vec3( 0.9, -0.9, -0.001);
	d->m->vtxs[2].pos = vec3( 0.9, -0.5, -0.001);
	d->m->vtxs[3].pos = vec3(-0.9, -0.5, -0.001);

	for (auto& v : d->m->vtxs)
		v.clr = vec4(0, 0, 0, 1);
	//

	// Setting up inputs
	inputs->next();

	inputs->mem["Dialogue"] = d;
	
	inputs->m[GLFW_MOUSE_BUTTON_LEFT] = [](int a, int m) {
		Dialogue* d = (Dialogue*)inputs->mem["Dialogue"];

		inputs->prev();
		d->m->show = false;
	};
	//
}

static Dialogue* create_dialogue(Renderer* r, std::string file_name = "Scripts/Script.txt") {
	Dialogue* d = new Dialogue();
	d->p = new Parser(file_name);
	d->r = r;
	d->_l = create_sprite(r);
	d->_r = create_sprite(r);
	d->_l->m->show = false;
	d->_r->m->show = false;

	init_dialogue(d);

	add_meshobj(d);

	return d;
}
