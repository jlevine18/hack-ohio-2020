#pragma once
#include "map.h"
namespace graphlogic {
	namespace fulkerson {
		class Model {
			Model();
			void SetMap(Map& map);
			Map GetMap();

		};
	}
}