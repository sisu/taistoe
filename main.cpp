#include "Game.hpp"
#include "SDL.h"
#include "physics.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;

Game game;

void handleKey(SDLKey k)
{
	if (k==SDLK_ESCAPE) game.done=1;
}
void handleEvent(SDL_Event e)
{
	switch(e.type) {
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_KEYDOWN:
			handleKey(e.key.keysym.sym);
			break;
	}
}

void handleMove()
{
	SDL_PumpEvents();
	Uint8* s = SDL_GetKeyState(0);
	Unit& p = *game.player;
	Vec3& m = p.m;
	m.x = s[SDLK_RIGHT] - s[SDLK_LEFT];
	m.z = s[SDLK_UP] - s[SDLK_DOWN];
	m.y = s['z'];
}

double getTime()
{
	return SDL_GetTicks()/1000.;
}

void gameLoop()
{
	game.init();
	double ot = getTime();
	while(!game.done) {
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			handleEvent(e);
		}

		double t = getTime();
		if (t < ot || t<ot+PHYS_FRAME) {
			SDL_Delay(10);
			continue;
		}
		while(t >= ot+PHYS_FRAME) {
			handleMove();
			game.updatePhysics();
			ot += PHYS_FRAME;
		}
		game.draw();
		SDL_GL_SwapBuffers();

		SDL_Delay(10);
	}
}

int main()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	atexit(SDL_Quit);
	SDL_SetVideoMode(800, 600, 0, SDL_OPENGL);

	gameLoop();
}
