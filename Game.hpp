#include "Unit.hpp"
#include "Area.hpp"
#include <vector>
struct Game {
	std::vector<Unit> units;
	Unit player;
	bool done;
	Area area;

	void updatePhysics();
	void draw();
	void init();

	void moveBots();
	void spawnBots();
	double botSpawnTime;
};
