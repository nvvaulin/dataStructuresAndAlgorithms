#include <iostream>     
#include <algorithm> 
#include <math.h>
#include <vector>
#include <limits>
#include <map>
using namespace std;
#define QNAN  std::numeric_limits<double>::quiet_NaN()
#define INF std::numeric_limits<double>::infinity()

/////////////////////Point/////////////////////////////
struct Point
{
	static Point NaP;
	static Point INFP;
	double x,y;
	Point(double _x=0,double _y=0) : x(_x), y(_y) {};	
	double operator*(Point a){
		return x*a.x+y*a.y;
	}
	Point operator-(Point a){
		Point res(x-a.x,y-a.y);
		return res;
	}
	Point operator+(Point a){
		Point res(x+a.x,y+a.y);
		return res;
	}

	bool operator==(Point a){
		return (x==a.x) && (y==a.y);
	}
	bool operator!=(Point a){
		return !(*this==a);
	}
	
};

Point Point::NaP(QNAN,QNAN);
Point Point::INFP(INF,INF);
double sqrAbs(Point x,Point y = Point(0,0) ){
	return (x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y);
};

//cos(ox^oy)
double cos(Point x, Point o,Point y){
	return (sqrAbs(x,o) + sqrAbs(y,o)-sqrAbs(x,y))/(2 * sqrt(sqrAbs(x,o)*sqrAbs(y,o)) );
};
/////////////////////Segment/////////////////////////////
struct Segment{
	Point x,y;
	Segment(Point _x,Point _y) : x(_x), y(_y) {};
};
/////////////////////line/////////////////////////////
class line{
public:
	double k,b;
	line(Point x,Point y){
		if (x==y)
			throw "incorrect line create";
		if (x.x==y.x)
			k = INF, b = x.x;
		else
			k = (x.y-y.y)/(x.x-y.x), b = y.y-k*y.x;
	}
	line(Segment x){
		line(x.x,x.y);
	}
	double operator()(double x){
		if ( (k == INF)&&(x == b) )
			return INF;
		if (k == INF)
			return QNAN;
		return k*x+b;
	}
	Point intersect(line l){
		if ( (k == INF)&&(l.k==INF) )
			if (b == l.b) 
				return Point::INFP;
			else
				return Point::NaP;
		if (k == INF)
			return Point(b,l(b));
		if (l.k == INF)
			return Point(l.b,(*this)(l.b));
		if (l.k==k)
			if (b == l.b)
				return Point::INFP;
			else
				return Point::NaP;
		double x =  (b-l.b)/(l.k-k);
		return Point(x,l(x));
	};
			
};

////////////////////////////////////////////////////////////////////////////////////////
Point intersection(Segment a,Segment b);
vector<Point> convexHull(vector<Point> v);

