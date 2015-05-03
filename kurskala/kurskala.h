#include <vector>
#include <iostream>
#include <algorithm>  
#include "dsu.h"

using namespace std;

typedef size_t vertex_id;

class graph
{
	
public:

	struct edge
	{
		vertex_id A,B;
		size_t W;
		edge(const  vertex_id& x,const  vertex_id& y,size_t _W) : A(min(x,y)), B(max(x,y)), W(_W){};
		bool operator<(const  edge& x) 
		{
			return (W < x.W);
		};
		operator size_t()
		{
			return W;
		};
		bool operator==(edge& e)
		{
			return (A == e.A) && (B == e.B) && (W == e.W);
		};
	};


	vector<edge> E; 

	void insert(size_t a,size_t b,size_t w)
	{
		E.push_back(edge(a,b,w));		
	};
	
	vector<edge> kurskala()
	{
		sort(E.begin(),E.end());
		dsu<vertex_id> s;
		vector<edge> res;
		for(auto i = E.begin(); i != E.end(); ++i)
		{
			if (s[i->A] != s[i->B])
			{
				s[i->A] = s[i->B];
				res.push_back(*i);
			};
		};

		return res;
	};

	size_t weight(vector<edge> x)
	{
		size_t res = 0;
		for(auto i = x.begin(); i != x.end(); ++i)
			res+= i->W;
		return res;
	};
};

