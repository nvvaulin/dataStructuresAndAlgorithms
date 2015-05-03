#include "Geometry.h"

bool compInter(Point x,Point y)
{
	return (x.x < y.x) || ( (x.x==y.x)&&(x.y<y.y) );
};


struct end_of_s
{
	Segment* s;
	bool p; // p => point is s.x and s.y else
	end_of_s(bool _p = false, Segment* _s = 0) : p(_p), s(_s) {}; 
	operator Point()
	{
		return (p) ? s->x : s->y;
	};
	//true if point is the first
	bool first(){
		return (compInter(s->x , s->y) == p);
	};
};

bool compInter1(end_of_s x,end_of_s y)
{
	return compInter( (x.p) ? x.s->x : x.s->y , (y.p) ? y.s->x : y.s->y );
};

//comparator for intersection : retun rtue if x.x > y.y or (x.x==x.y) and (x.y < y.y)

Point first(Segment* s)
{
	return (compInter(s->x,s->y)) ? s->x : s->y;
};

class compInterForMap
{
public:
	bool operator()(Segment* x,Segment* y){
		return first(x).y > first(y).y;
	};
};


Point intersection(Segment a,Segment b)
{
	line la(a) ,lb(b);
	Point res = la.intersect(lb);
	if (res == Point::NaP)
		return res;
	if (res == Point::INFP)
		if ((a.x.x >= min(b.x.x,b.y.x))&&(a.x.x <= max(b.x.x,b.y.x)))
			return a.x;
		else
			return a.y;
	if (res.x <= min(max(a.x.x,a.y.x),max(b.x.x,b.y.x)) &&  res.x >= max(min(a.x.x,a.y.x),min(b.x.x,b.y.x)) 
	&&  res.y <= min(max(a.x.y,a.y.y),max(b.x.y,b.y.y)) &&  res.y >= max(min(a.x.y,a.y.y),min(b.x.y,b.y.y)))
		return res;
	return Point::NaP;
};

bool intersection(vector<Segment> &v)
{
	vector<end_of_s> points;
	map<Segment*,bool,compInterForMap> tttt;
	for(auto i : v)
	{
		points.push_back(end_of_s(true,&i));
		points.push_back(end_of_s(false,&i));
	};
	sort(points.begin(),points.end(),compInter1);
	for(auto i : points)
	{
		auto upper = tttt.upper_bound(i.s);
		auto lower = tttt.lower_bound(i.s);
		if (i.first())
		{			
			if (upper != tttt.end()){
				if (intersection(*(upper->first),*(i.s) ) != Point::NaP)
					return true;
			};
			if (lower != tttt.end()){
				if (intersection(*(lower->first),*(i.s) ) != Point::NaP)
					return true;
			};
			tttt.insert( pair<Segment*,bool>(i.s,false) );
		}
		else
		{
			if ( (upper != tttt.end()) && (lower != tttt.end()) )
				if (intersection(*(upper->first),*(lower->first) ) != Point::NaP)
					return true;
				tttt.erase(tttt.find(i.s));
		};
	};
	return false;
};



