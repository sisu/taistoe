#include <GL/glu.h>
#include <GL/gl.h>
#include "Unit.hpp"
#include "Game.hpp"
#include "cube.hpp"
#include <vector>
using namespace std;


void drawUnit(Unit& u)
{
	glPushMatrix();
	Vec3 p = u.p;
	glTranslatef(p.x, p.y, -p.z);
	drawcube();
	glEnd();
}

void setProjection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 4./3., .1, 1000);
	glMatrixMode(GL_MODELVIEW);
}
void setLights()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float pos[] = {1,1,1,0};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
}

void drawFrame(Game& g)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setProjection();
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	setLights();

	glTranslatef(0, 0, -30);
	glRotatef(40, 1, 0, 0);

	for(size_t i=0; i<g.units.size(); ++i) {
		Unit& u = g.units[i];
		drawUnit(u);
	}
}
