#include <vector>
#include <memory>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <climits>

using namespace std;


struct char128
{
	char c[128];
}; 

enum COLOR
{
	WHITE = 0,
	GRAY = 1,
	BLACK = 2
};
class graph
{
public:
	struct vertex
	{
		unordered_map<size_t,shared_ptr<char128> > edges;
		size_t n;//number of the vertex
		vertex(int _n) : n(_n) {};
		bool operator<(const vertex& x)const
		{
			return n < x.n;
		};
	};
private:

	vector<vertex> vertexes;

public:
	vector< unordered_set<size_t> > find_sccg() const;	
	vector< vector< pair<pair<size_t,size_t>, shared_ptr<char128> > > > find_edges_of_sccg() const;
	graph(size_t n)
	{
		for(size_t i = 0; i < n; ++i)
			vertexes.push_back(vertex(i));
	};
	
	void insert_edge(size_t a,size_t b)
	{
		if( a < vertexes.size() && b < vertexes.size())
			vertexes[a].edges[b];
	};

	void delete_edge(size_t a,size_t b)
	{
		if( a < vertexes.size() && b < vertexes.size())
			vertexes[a].edges.erase(b);
	};

	void insert_word(size_t a,size_t b,shared_ptr<char128> s)
	{
		if( a < vertexes.size() && b < vertexes.size())
			for(size_t k = 0; k < 2; ++k)
			{
				auto i = vertexes[a].edges.find(b);
				if(i != vertexes[a].edges.end())
					i->second = s;
				swap(a,b);
			};
	};

	void delete_word(size_t a,size_t b)
	{
		if( a < vertexes.size() && b < vertexes.size())
			for(size_t k = 0; k < 2; ++k)
			{
				auto i = vertexes[a].edges.find(b);
				if(i != vertexes[a].edges.end())
					i->second.reset();
				swap(a,b);
			};
	};
};