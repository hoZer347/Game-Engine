#pragma once

#include "Renderer.h"
#include "Mesh.h"
#include "Text.h"

#include <functional>
#include <fstream>
#include <map>

class Dialogue : public MeshObj {
public:
	void update();

	Renderer* renderer = NULL;
	std::fstream file;
	std::map<std::string, std::function<void(Dialogue*, std::string)>> f;
};

static Dialogue* create_dialogue(Renderer* r, std::string file_name="Script.txt") {
	Dialogue* d = new Dialogue();
	
	d->renderer = r;
	d->file = std::fstream(file_name);

	OBJS.push_back(d);

	return d;
}
