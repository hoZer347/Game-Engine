#include "Stage.h"

#include "Object.h"
#include "Spooler.h"

#include <atomic>

namespace stage {
	size_t
		STAGE=0,
		NUM_STAGES=0;

	bool KILL = false;

	std::vector<size_t> inds(spooler::MAX_CORES);

	void manage() {
		while (!KILL) {
			NOT_DONE:
			
			for (auto i : inds)
				if (i < obj::OBJS.size())
					goto NOT_DONE;

			for (size_t i = 0; i < inds.size(); i++)
				inds[i] = i;

			STAGE++;
			if (STAGE > NUM_STAGES)
				STAGE = 0;
		};
	};

	void kernel(size_t t) {
		size_t& i = inds[t];

		while (!KILL) {
			for (; i < obj::OBJS.size(); i+=spooler::MAX_CORES)
				obj::OBJS[i]->stage(STAGE);
		};
	};

	void init(unsigned char t) {
		NUM_STAGES = t;

		spooler::threads.push_back(std::thread(manage));

		for (size_t i = 0; i < spooler::MAX_CORES; i++)
			spooler::threads.push_back(std::thread(kernel, i));
	};

	void close() {
		KILL = true;
	};
};
