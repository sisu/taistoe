#include "Unit.hpp"
#include <vector>
struct Game {
	std::vector<Unit> units;
	Unit* player;
	bool done;

	void updatePhysics();
	void draw();
	void init();
};
