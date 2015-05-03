#include <vector>
#include <stack>
#include <unordered_map>
#include <climits>
#include <algorithm>
using namespace std;

enum COLOR
{
	WHITE = 0,
	GRAY = 1,
	BLACK = 2
};
class graph
{
public:

	typedef size_t  vertex_id;

	struct vertex : public unordered_map<vertex_id,size_t >
	{
	private:
		vertex_id n;//number of the vertex
	public:
		vertex() {};

		vertex(int _n) : n(_n) {};
		bool operator<(const vertex& x)const
		{
			return n < x.n;
		};
		operator vertex_id()const
		{
			return n;
		};
		vertex_id operator=(vertex_id x)
		{
			return n = x;
		};
	};
	struct edge : pair<vertex_id,vertex_id>
	{
		edge(vertex_id x,vertex_id y) : pair<vertex_id,vertex_id>(x,y){};
		bool operator<(const  edge& x) 
		{
			return (first < x.first) || (first == x.first && second < x.second);
		};
		operator __int64()const//for hash<__int64>
		{
			__int64 res = first;
			res = res << 32;
			res += second;
			return res;
		};
		edge operator-()
		{
			return edge(second,first);
		};
	};
private:

	vector<vertex> V;
	double p;

	vector<vertex_id> get_path(vertex_id a,vertex_id b);

	class _preFlow
	{
		vertex_id source, drain;
		unordered_map<edge,int,hash<__int64> > f;
		vector<int> overload;
		vector<int> h;
		vector<vertex> V;
		double p;

		void push(edge e);// e = <u;v> u is overload; e in f

		void relabel(vertex& u);// e.A is overload

		bool discharge(vertex::const_iterator& current, vertex& u);//return true if h[u] was changed

		void initPreFlow();

		
	public:

		_preFlow(vector<vertex>& _V, vertex_id _s,vertex_id _d);
		int operator()();//get max flow
	};

public:
	graph(size_t n,double _p)
	{
		p = _p;
		V.reserve(n);
		for(vertex_id i = 0; i < n; ++i)
		{
			V.push_back(vertex(i));
			V.back().reserve(n*p+1);
		};
	};
	
	void insert_edge(vertex_id a,vertex_id b,size_t w)
	{
		if( a < V.size() && b < V.size())
		{
			V[a][b] = w;
			V[b][a] = w;
		};
	};

	void delete_edge(vertex_id a,vertex_id b)
	{
		if( a < V.size() && b < V.size())
		{
			V[a].erase(b);
			V[b].erase(a);
		};
	};
	
	void clear()
	{
		V.clear();
	};
		
	int ford_falkerson(vertex_id a,vertex_id b);

	int preFlow(vertex_id a, vertex_id b)
	{
		if (get_path(a,b).size() < 0)// if there is no paths 
			return -1;
		return _preFlow(V,V[a],V[b])();
	};

};