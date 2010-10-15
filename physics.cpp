#include "physics.hpp"
#include "Unit.hpp"
#include "Area.hpp"
#include <iostream>
using namespace std;

void fixHit(Unit& u, Vec3 old, Area& a)
{
}

void moveUnits(Unit* us, int n, Area& a)
{
	for(int i=0; i<n; ++i) {
		Unit& u = us[i];
		Vec3 m = u.m;
		Vec3 p = u.p;
		if (u.p.y==0) {
			m.y *= 1.5;
			u.v = 16*m;
		} else {
			m.y = 0;
			u.v += .5*m;
		}
		u.v.y -= PHYS_FRAME * 100;
//		cout<<"m "<<u.m<<'\n';

		u.p += PHYS_FRAME * u.v;
		u.p.y = max(0., u.p.y);
//		cout<<u.p<<'\n';
		fixHit(u, p, a);
	}
}
