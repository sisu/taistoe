#include "physics.hpp"
#include "Unit.hpp"
#include "Area.hpp"
#include <iostream>
#include <cassert>
using namespace std;

void limitPoint(Vec3& v, Vec3 old, Vec3 p, Vec3 d)
{
	if (v.y >= p.y) return;
	d = normalize(d);
	Vec3 p0 = p;
	p += d * PLAYER_SIZE;
	if (dot(v-p, d) >= 0) return;
	if (old.y >= p.y) {
		v.y = p.y;
		return;
	}
	p.y = v.y;
//	cout<<"fixing "<<v<<' '<<p<<' '<<d<<' '<<dot(d,p-v)<<" ; "<<old<<" ; "<<p0<<'\n';
	v += (1+1e-5) * dot(d,p-v) * d;
}
// FIXME: This function is used for taisto2-style boundary checking,
// which may lead to units getting inside walls.
// This function should be removed and calls replaced by calls to limitPoint etc.
void fixPointDist(Vec3& v, Vec3 old, Vec3 p) {
	if (v.y >= p.y) return;
	double dst = PLAYER_SIZE;
	double y0 = p.y;
	p.y = v.y;
	Vec3 d = v-p;
	if (length2(d) >= dst*dst) return;
	if (old.y >= y0) {
		v.y = y0;
		return;
	}

	// this is for avoiding some cases where we go inside a wall but it might not
	// work always
	if (dot(d,old-p)<0) d=-d;

	v = p + dst*normalize(d);
}
void fixHit(Unit& u, Vec3 old, Area& a)
{
	assert(old.y >= a.height(old.x, old.z));

	Vec3& p = u.p;
	limitPoint(p, old, Vec3(0,1e20,p.z), Vec3(1,0,0));
	assert(p.x >= 0);
	limitPoint(p, old, Vec3(a.w,1e20,p.z), Vec3(-1,0,0));
	assert(p.x < a.w);
	limitPoint(p, old, Vec3(p.x,1e20,0), Vec3(0,0,1));
	assert(p.z >= 0);
	limitPoint(p, old, Vec3(p.x,1e20,a.h), Vec3(0,0,-1));
	assert(p.z < a.h);

//	cout<<"yeah "<<p<<'\n';

#if 1
	int ix=old.x, iz=old.z;
	for(int i=0; i<3; ++i)
		for(int j=0; j<3; ++j) {
			if (i==1&&j==1) continue;
			if (i!=1&&j!=1) continue;
			// FIXME: these may be wrong when floor(old)!=floor(p)
			double zs[] = {(double)iz, p.z, iz+1.};
			double xs[] = {(double)ix, p.x, ix+1.};
			Vec3 v(xs[j], a.height(ix-1+j, iz-1+i), zs[i]);
			Vec3 pp = p;
			Vec3 dir(1-j, 0, 1-i);
			limitPoint(p, old, v, dir);
//			if (p!=pp) cout<<"change at "<<i<<' '<<j<<": "<<p<<' '<<pp<<'\n';
		}
	for(int i=0; i<2; ++i)
		for(int j=0; j<2; ++j) {
			double zs[] = {(double)iz, iz+1.};
			double xs[] = {(double)ix, ix+1.};
			Vec3 v(xs[j], a.height(ix-1+2*j, iz-1+2*i), zs[i]);
			Vec3 pp = p;
			if (i!=1&&j!=1) {
				// FIXME: handle corners in proper way
				fixPointDist(p, old, v);
//				if (p.x!=pp.x || p.z!=pp.z) cout<<"fixPointDist change @ "<<i<<' '<<j<<": "<<p<<' '<<pp<<'\n';
				continue;
			}
		}
#endif

	p.y = max(p.y, a.height(p.x,p.z));
//	cout<<"lol "<<a.height(p.x,p.z)<<' '<<old.y<<'\n';
//	limitPoint(p, old, Vec3(p.x,a.height(p.x,p.z),p.z), Vec3(0,1,0));

#if 0
	p.x = max(p.x, 1e-5);
	p.z = max(p.z, 1e-5);
	p.x = min(p.x, a.w-1e-5);
	p.z = min(p.z, a.h-1e-5);
	double y = a.height(p.x,p.z);
	if (p.y < y) {
//		cout<<"down "<<p.y<<' '<<y<<' '<<old.y<<'\n';
		if (old.y >= y)
			p.y = y;
		else {
		}
	}
#endif
}

void moveUnits(Unit* us, int n, Area& a)
{
	for(int i=0; i<n; ++i) {
		Unit& u = us[i];
		Vec3 m = u.m;
		Vec3 p = u.p;
		if (u.p.y==a.height(p.x,p.z)) {
			m.y *= 1.5;
			u.v = 16*m;
		} else {
			m.y = 0;
			u.v += .5*m;
		}
		u.v.y -= PHYS_FRAME * 100;
//		cout<<"m "<<u.m<<'\n';

		u.p += PHYS_FRAME * u.v;
//		cout<<u.p<<'\n';
		fixHit(u, p, a);
//		cout<<"fixHit res "<<u.p<<'\n';
	}
}
