#pragma once

#include "Renderer.h"
#include "Mesh.h"
#include "Text.h"

#include <fstream>

class Dialogue : public MeshObj {
public:
	void update();

	std::fstream f;
};

static Dialogue* create_dialogue(std::string file_name="Script.txt") {
	Dialogue* d = new Dialogue();

	OBJS.push_back(d);

	d->f = std::fstream(file_name);

	return d;
}
