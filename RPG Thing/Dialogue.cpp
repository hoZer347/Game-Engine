#include "Dialogue.h"

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