#include "Animation.h"

std::map<std::string, Animation*> ANMT;

Animation::Animation() {
	animate = false;
}

void Animation::update() {
	f(this);
}

Animation* create_animation(std::string s) {
	Animation* a = new Animation();

	ANMT[s] = a;
	OBJS.push_back(a);

	return a;
};

void stop_animations() {
	for (auto& i : ANMT)
		i.second->animate = false;
};
