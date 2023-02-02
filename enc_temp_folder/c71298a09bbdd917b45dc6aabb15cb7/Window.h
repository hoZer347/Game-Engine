#pragma once

namespace window {
	struct Window;

	namespace game {
		Window* create();
	}

	namespace res {
		Window* create();
	}

	void init(Window*);
	void reset(Window*);
};
