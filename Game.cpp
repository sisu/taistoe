#include "Game.hpp"
#include "physics.hpp"
#include "draw.hpp"
#include <iostream>
using namespace std;

void Game::updatePhysics()
{
	moveUnits(&units[0], units.size(), area);
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
	area.generate(64,256);
}
