#pragma once

#include "Renderer.h"
#include "Parser.h"
#include "Mesh.h"
#include "Text.h"

#include <functional>
#include <fstream>
#include <string>
#include <map>

enum {
	START = 0,
	END = 1
};

class Dialogue : public MeshObj {
public:
	void update();

	Parser* p = NULL;
	Renderer* renderer = NULL;
	unsigned short state = START;
	std::map<std::string, std::function<void(Dialogue*, std::string)>> f;
};

static Dialogue* create_dialogue(Renderer* r, std::string file_name="Scripts/Script.txt") {
	Dialogue* d = new Dialogue();
	d->p = new Parser(file_name);
	d->renderer = r;

	OBJS.push_back(d);

	return d;
}
