#include "Game.hpp"
#include "physics.hpp"
#include "draw.hpp"
#include "util.hpp"
#include <iostream>
#include <cmath>
using namespace std;

void Game::updatePhysics()
{
	units[0] = player;

	spawnBots();
	moveBots();
	moveUnits(&units[0], units.size(), area);
	player = units[0];
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
	player = units[0];
	area.generate(64,256);
	botSpawnTime = 0;
}
void Game::moveBots()
{
	for(size_t i=0; i<units.size(); ++i) {
		Unit& u = units[i];
		if (u.type == 0) continue;
		double a = rndf()*2*M_PI;
		u.m.x = cos(a);
		u.m.z = sin(a);
	}
}
void Game::spawnBots() {
//	cout<<"bst: "<<botSpawnTime<<" ; "<<PHYS_FRAME<<'\n';
	botSpawnTime -= PHYS_FRAME;
	if (botSpawnTime > 0) return;
	botSpawnTime += 2;

	Unit b = {};
	b.type = 1;
	double x = floor(area.w * rndf()) + .5;
	double y = floor(area.h * rndf()) + .5;
	b.p = Vec3(x, area.height(x,y), y);
	units.push_back(b);
	cout<<"spawning bot @ "<<b.p<<'\n';
}
