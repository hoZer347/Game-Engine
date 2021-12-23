#include "Animation.h"

std::map<std::string, Animation*> ANMT;

Animation::Animation() {
	animate = false;
}

void Animation::update() {
	f(this);
}
