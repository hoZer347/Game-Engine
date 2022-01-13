#pragma once

#include "Mesh.h"

#include <functional>
#include <string>

class Parser;
class Sprite;
class Renderer;

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

extern Dialogue* create_dialogue(Renderer*, std::string="Scripts/Script.txt");
