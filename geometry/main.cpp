#include "Geometry.h"

void main()
{
	double a[] = {0,0,0,1,-1,0,1,1,-5,1,2,4,1,11,5,5};
	vector<Segment> v;
	for( int i = 0; i<4; ++i)
		v.push_back(Segment(Point(a[4*i],a[4*i+1]),Point(a[4*i+2],a[4*i+3])) );
	bool b = intersection(v);
};