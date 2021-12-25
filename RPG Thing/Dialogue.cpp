#include "Dialogue.h"

void Dialogue::update() {
	switch (state) {
	case START:
		if (p->next())
			std::cout << p->line << std::endl;
		else
			return;

		break;
	case END:
		break;
	default:
		break;
	}
}
