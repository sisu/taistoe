#include <GL/glu.h>
#include <GL/gl.h>
#include "Unit.hpp"
#include "Game.hpp"
#include "cube.hpp"
#include "Area.hpp"
#include <vector>
using namespace std;


void drawUnit(Unit& u)
{
	glPushMatrix();
	Vec3 p = u.p;
	glTranslatef(p.x, p.y+.5, -p.z);
	glScalef(.5,.5,.5);
	glColor3f(.3,.3,.8);
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
	glEnable(GL_COLOR_MATERIAL);
}
void drawArea(Area& a)
{
	glColor3f(.3,.8,.3);
	const int qv[4][2] = {{0,0},{1,0},{1,1},{0,1}};
	glBegin(GL_QUADS);
	for(int y=0; y<a.h; ++y) {
		for(int x=0; x<a.w; ++x) {
			double h = a(x,y);
			glNormal3f(0,1,0);
			for(int i=0; i<4; ++i) glVertex3f(x+qv[i][0], h, -y-qv[i][1]);

			if (y && h!=a(x,y-1)) {
				double hh = a(x,y-1);
				glNormal3f(0,0,h<hh?1:-1);
				for(int i=0; i<4; ++i) glVertex3f(x+qv[i][0], qv[i][1]?h:hh, -y);
			}
			if (x && h!=a(x-1,y)) {
				double hh = a(x-1,y);
				glNormal3f(h<hh?1:-1,0,0);
				for(int i=0; i<4; ++i) glVertex3f(x, qv[i][1]?h:hh, -y-qv[i][0]);
			}
		}
	}
	glEnd();
}

void drawFrame(Game& g)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setProjection();
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	setLights();

	glTranslatef(0, 0, -20);
	glRotatef(40, 1, 0, 0);
	Unit& pl = *g.player;
	glTranslatef(-pl.p.x, 0, pl.p.z);

	drawArea(g.area);

	for(size_t i=0; i<g.units.size(); ++i) {
		Unit& u = g.units[i];
		drawUnit(u);
	}
}
