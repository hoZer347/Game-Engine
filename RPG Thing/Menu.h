#pragma once

#include "Mesh.h"

#include <vector>
#include <functional>

struct Room;
class Inputs;

class option {
	virtual void on()=0;
	virtual void off()=0;
	virtual bool intersect(Inputs*)=0;
	std::function<void(Room*)> f;
};

class Menu : public MeshObj {
public:
	void clear() { o.clear(); };

protected:
	std::vector<option*> o;
};
