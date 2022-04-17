#include "Geo.h"

#include "Mesh.h"

namespace geo {
	struct Geo : mesh::Mesh {

	};

	namespace square {
		Geo* create() {
			Geo* g = new Geo();

			return g;
		};
	};

	namespace cube {
		Geo* create() {
			Geo* g = new Geo();

			return g;
		};
	};
};
