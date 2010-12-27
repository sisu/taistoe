#include "Area.hpp"
#include "util.hpp"
#include <cstring>
#include <algorithm>
using namespace std;

void Area::generate(int ww, int hh)
{
	w=ww;
	h=hh;
	delete[] a;
	a = new double[w*h];
	memset(a,0,w*h*sizeof(a[0]));
	for(int i=0; i*i<6*w*h; ++i) {
		int x0 = rng()%w;
		int y0 = rng()%h;
		const int s=10;
		int ww = min(int(1+(rng()%s)), w-x0);
		int hh = min(int(1+(rng()%s)), h-y0);
		double yy = 5*rndf();
		for(int y=0; y<hh; ++y) for(int x=0; x<ww; ++x) a[w*(y0+y) + x0+x] = yy;
	}
}
