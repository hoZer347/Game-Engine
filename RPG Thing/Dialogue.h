#pragma once

#include "CameraMovement.hpp"
#include "Renderer.h"
#include "Sprite.h"
#include "Inputs.h"
#include "Parser.h"
#include "Mesh.h"
#include "Text.h"

#include <functional>
#include <fstream>
#include <string>
#include <map>

class Dialogue : public MeshObj<Dialogue> {
public:
	~Dialogue();
	void update();

	Parser* p = NULL;
	Renderer* r = NULL;

	Sprite* _l = NULL;
	Sprite* _r = NULL;
	std::string s;
	
	unsigned char state = 0;
};
