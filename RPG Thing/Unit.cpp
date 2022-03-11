#include "Unit.h"

#include "Sprite.h"
using sprite::Sprite;

#include "Object.h"
using namespace obj;

namespace unit {
	enum {
		NUM_STATS=10,
	};

	class Unit :
		public Obj {
		unsigned char stats[NUM_STATS];
		Sprite* s = NULL;
	};



	class UnitManager :
		public Manager<Unit> {
	public:
	private:
	};

	UnitManager UNIT;



	Unit* create(const char* file_name) {
		return NULL;
	};
};
