#pragma once

#include "Menu.h"

#include "Inputs.h"
#include "Text.h"

class TextMenu : public Menu {
	class text_option : public option {
	public:
		friend class TextMenu;

		text_option(Text* text) {
			t = text;
		}

		void on() {
			for (auto& i : t->l)
				for (auto& j : i.second)
					i.first->vtxs[j].clr = on_clr;
		}

		void off() {
			for (auto& i : t->l)
				for (auto& j : i.second)
					i.first->vtxs[j].clr = off_clr;
		}

		bool intersect(Inputs* i) {
			
		}

	protected:
		vec4 on_clr=vec4(1), off_clr=vec4(0);
		Text* t = NULL;
	};

	option* get(Inputs* i) {

	}

	void add(Text* t, vec4 on_clr = vec4(1), vec4 off_clr = vec4(0)) {
		text_option* t_o = new text_option(t);
		t_o->on_clr = on_clr;
		t_o->off_clr = off_clr;
		o.push_back(t_o);
	}

protected:
};
