#include "Geometry.h"

class compCos
{
	Point o1,o2;
public:
	compCos(Point _o1, Point _o2 = Point(1,0) ) : o1(_o1), o2(_o1+_o2) {};
	bool operator()(Point x, Point y){
		if (x == o1)
			return true;
		if (y == o1)
			return false;
		double cosx = cos(x,o1,o2);
		double cosy = cos(y,o1,o2);
		if (cosx == cosy)
			return x.x < y.x;
		else
			return cosx > cosy;
	};
};
//angle between vector oa and ob is positive
bool rotLeft(Point a, Point o,Point b)
{
	if (a == b) return false;
	a = a-o;
	b = b-o;
	return -a.x*b.y+a.y*b.x > 0;
};

vector<Point> convexHull(vector<Point> v)
{
	vector<Point> res(1,v[0]);
	//find the undermosts and the leftest from undermosts
	for(int i = 1; i<v.size(); ++i)
		if ( (v[i].y < res[0].y) || ((v[i].y == res[0].y)&&((v[i].x < res[0].x))) )
			res[0] = v[i];

	//order by increase rotation points round the point res[0] and vector (1,0) and axis x desc (if similar angle)
	compCos comparator(res[0]);
	sort(v.begin(),v.end(),comparator);

	res.push_back(v[1]);
	res.push_back(v[2]);
	for (size_t i = 3; i<v.size(); ++i)
	{
		while (!rotLeft(res[res.size()-2],res.back(),v[i]) )
			{
				res.pop_back();
			};
		res.push_back(v[i]);
	};
	return res;
};








