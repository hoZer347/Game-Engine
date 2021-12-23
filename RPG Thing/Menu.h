#pragma once

#include "Mesh.h"
#include "Renderer.h"

#include <vector>
#include <functional>

class option : public MeshObj {
	virtual void on()=0;
	virtual void off()=0;
	virtual bool intersect(Renderer*)=0;
	std::function<void()> f;
};

class Menu : public MeshObj {
public:
	void update() {};
	void clear() { o.clear(); };

protected:
	std::vector<option*> o;
};


