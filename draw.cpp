#include <GL/glu.h>
#include <GL/gl.h>
#include "Unit.hpp"
#include "Game.hpp"
#include "cube.hpp"
#include "Area.hpp"
#include "physics.hpp"
#include <vector>
using namespace std;


void drawUnit(Unit& u)
{
	glPushMatrix();
	Vec3 p = u.p;
	double s = PLAYER_SIZE;
	glTranslatef(p.x, p.y, -p.z);
	glScalef(s,s,s);
	glColor3f(.3,.3,.8);
//	drawcube();
	const int n = 16;
	double h = 2;
	for(int j=0; j<2; ++j) {
		glBegin(j?GL_TRIANGLE_FAN:GL_TRIANGLE_STRIP);
		glNormal3f(0,1,0);
		for(int i=0; i<n; ++i) {
			double a = 2*M_PI*i/n;
			double sa=sin(a), ca=cos(a);
			if (j==0) {
				glNormal3f(ca,0,sa);
				glVertex3f(ca, 0, sa);
			}
			glVertex3f(ca, h, sa);
		}
		if (j==0) {
			glNormal3f(1,0,0);
			glVertex3f(1,0,0);
			glVertex3f(1,h,0);
		}
		glEnd();
	}
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
void setHeightColor(double h)
{
	if (.4*h <= .5) {
		glColor3f(.3*h, .5+.4*h, .3*h);
	} else {
		double hh = h - .5/.4;
		double s = .3 * .5/.4;
		glColor3f(s + .3*hh, 1-.2*hh, s+.05*hh);
	}
}
void drawArea(Area& a)
{
	glColor3f(.3,.8,.3);
	const int qv[4][2] = {{0,0},{1,0},{1,1},{0,1}};
	glBegin(GL_QUADS);
	for(int y=0; y<a.h; ++y) {
		for(int x=0; x<a.w; ++x) {
			double h = a.height(x,y);
			setHeightColor(h);
			glNormal3f(0,1,0);
			for(int i=0; i<4; ++i) glVertex3f(x+qv[i][0], h, -y-qv[i][1]);

			if (y && h!=a.height(x,y-1)) {
				double hh = a.height(x,y-1);
				glNormal3f(0,0,h<hh?1:-1);
				for(int i=0; i<4; ++i) glVertex3f(x+qv[i][0], qv[i][1]?h:hh, -y);
			}
			if (x && h!=a.height(x-1,y)) {
				double hh = a.height(x-1,y);
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
