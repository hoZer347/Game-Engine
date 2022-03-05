#include "Inputs.h"

#include "GLFW/glew.h"
#include "GLFW/glfw3.h"

#include "Window.h"

#include "Object.h"
using namespace obj;

namespace inputs {
	class Inputs : public Obj {
	public:
		~Inputs() {
			delete _prev;
		};

		void setup() {

		};

		void update() {
			glfwPollEvents();
		};
		
		void render() {

		};

		Inputs
			*_next = NULL,
			*_prev = NULL;
	};

	Inputs* INPUTS = NULL;

	void next() {
		Inputs* i = new Inputs();

		if (INPUTS) {
			INPUTS->_next = i;
			i->_prev = INPUTS;
			INPUTS = INPUTS->_next;
		} else
			INPUTS = i;
	};

	void prev() {
		INPUTS = INPUTS->_prev;
		delete INPUTS->_next;
		INPUTS->_next = NULL;
	};

	void close() {
		delete INPUTS;
	};
};
