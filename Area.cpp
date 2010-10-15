#include "Area.hpp"
#include "util.hpp"
#include <cstring>

void Area::generate(int ww, int hh)
{
	w=ww;
	h=hh;
	delete[] a;
	a = new double[w*h];
	memset(a,0,w*h*sizeof(a[0]));
	for(int i=0; i*i<5*w*h; ++i)
		a[rng()%(w*h)] = 2*rndf();
}
