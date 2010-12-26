#ifndef AREA_HPP
#define AREA_HPP

struct Area {
	int w,h;
	double* a;
	double height(int x, int y) {
		if (x<0||y<0||x>=w||y>=h) return 1e20;
		return a[y*w+x];
	}
	void generate(int w, int h);
};

#endif
