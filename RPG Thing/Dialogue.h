#pragma once

#include "Renderer.h"
#include "Mesh.h"
#include "Text.h"

#include <fstream>

class Dialogue : public MeshObj {
public:
	void update();

private:

};

static Dialogue* create_dialogue() {
	Dialogue* d = new Dialogue();

	return d;
}
