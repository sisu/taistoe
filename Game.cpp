#include "Game.hpp"
#include "physics.hpp"
#include "draw.hpp"

void Game::updatePhysics()
{
	moveUnits(&units[0], units.size());
}
void Game::draw()
{
	drawFrame(*this);
}
void Game::init()
{
	done=0;
	units.clear();
	units.push_back(Unit());
	player = &units[0];
}
