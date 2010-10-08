#include "physics.hpp"
#include "Unit.hpp"
#include <iostream>
using namespace std;

void moveUnits(Unit* us, int n)
{
	for(int i=0; i<n; ++i) {
		Unit& u = us[i];
		Vec3 m = u.m;
		if (u.p.y==0) {
			u.v = 20*m;
		} else {
			m.y = 0;
			u.v += .5*m;
		}
		u.v.y -= PHYS_FRAME * 100;
//		cout<<"m "<<u.m<<'\n';

		u.p += PHYS_FRAME * u.v;
		u.p.y = max(0., u.p.y);
//		cout<<u.p<<'\n';
	}
}
