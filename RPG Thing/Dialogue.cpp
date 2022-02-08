#include "Dialogue.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"
#include "Inputs.h"

#include "RendererActions.h"
#include "Renderer.h"
#include "Parser.h"
#include "Sprite.h"
#include "Inputs.h"
#include "Mesh.h"
#include "Text.h"

Dialogue::~Dialogue() {
	if (p) delete p;
}

void Dialogue::update() {
	m->trns = mat4(1) * inverse(r->c->mvp);

	switch (state) {
	case 0:
		p->next();
		while (!p->cmds.empty()) {
			s = p->cmds.front();
			p->cmds.pop();

			std::cout << s << std::endl;

			if (s == "") return;
			
			else if (s == "Left") {
				std::cout << p->cmds.front() << std::endl;
				bind_texture(_l, ("Textures/" + p->cmds.front()).c_str());
				p->cmds.pop();
				_l->m->show = true;
			}
			
			else if (s == "Right") {
				std::cout << p->cmds.front() << std::endl;
				bind_texture(_r, ("Textures/" + p->cmds.front()).c_str());
				_r->m->inds[0] = 1;
				_r->m->inds[1] = 2;
				_r->m->inds[2] = 3;
				_r->m->inds[3] = 0;
				_r->m->trns *= translate(mat4(1), vec3(1, 0, 0));
				p->cmds.pop();
				_r->m->show = true;
			};
		}
		state++;
		break;

	case 1:
		break;

	default:
		state = 0;
		break;
	}
}

Dialogue* create_dialogue(Renderer* r, std::string file_name) {
	Dialogue* d = new Dialogue();
	d->p = new Parser(file_name);
	d->r = r;
	d->_l = create_sprite();
	d->_r = create_sprite();
	d->_l->m->show = false;
	d->_r->m->show = false;

	// Setting text box
	d->m = create_square();

	d->m->vtxs[0].pos = vec3(-0.9, -0.9, -0.001);
	d->m->vtxs[1].pos = vec3(0.9, -0.9, -0.001);
	d->m->vtxs[2].pos = vec3(0.9, -0.5, -0.001);
	d->m->vtxs[3].pos = vec3(-0.9, -0.5, -0.001);

	for (auto& v : d->m->vtxs)
		v.clr = vec4(0, 0, 0, 1);
	//

	// Setting up inputs
	new_inputs();

	inputs->mem["Dialogue"] = d;

	inputs->m[GLFW_MOUSE_BUTTON_LEFT] = [](int a, int m) {
		Dialogue* d = (Dialogue*)inputs->mem["Dialogue"];

		prev_inputs();
		d->m->show = false;
		delete_meshobj((_MeshObj*)d);
	};
	//

	make_meshobj(d);

	return d;
}
