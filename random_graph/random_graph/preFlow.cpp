#include "graph.h"




void graph::_preFlow::push(edge e)// e = <u;v> u is overload; e in f
{
	int w = min( overload[e.A], (int)(V[e.A][e.B]) - f[e] );		
	f[e] += w;
	f[-e] -= w;
	overload[e.A] -= w ;
	overload[e.B] += w;
};

void graph::_preFlow::relabel(vertex& u)// u is overload;
{
	int m = 3*V.size();
	for(const auto& i : u)
	{
		vertex_id v = i.first;
		if  ( f[edge(u,v)] - i.second > 0 )
			if (m > h[v])
				m = h[v];
	};
	h[u] = m + 1;
};


bool graph::_preFlow::discharge(vertex::const_iterator& current, vertex& u)//return true if h[u] was changed
{
	size_t pref_h = h[u];
	while ( overload[u] > 0 )
	{
		if(current == u.end())
		{
			current = u.begin();
			relabel(u);
		}
		else
			if (V[u][current->first] - f[edge(u,current->first)] > 0 && h[u] == h[current->first] + 1 )
				push(edge(u,current->first));
			else
				++current;
	};
	return pref_h != h[u];
};

void graph::_preFlow::initPreFlow()
{
	//init h
	h[source] = V.size();

	//init f and overload
	f.reserve(V.size()*V.size());
	for(const auto& i : V)
		for(const auto& j : i)
		{
			f[edge(i,j.first)] = 0;
			f[edge(j.first,i)] = 0;
		};
	for(const auto& i : V[source])
	{
		edge e(source,i.first);
		f[e] += i.second;
		f[-e] -= i.second;
		overload[e.A] -= i.second;
		overload[e.B] = i.second;
	};

};

graph::_preFlow::_preFlow(vector<vertex>& _V, vertex_id _s,vertex_id _d) :  V(_V) , source(_s), drain(_d), overload(_V.size(),0), h(_V.size(),0)
{

	initPreFlow();

	//init L and current;
	vector<vertex::const_iterator> current(V.size());
	vector<vertex_id> L;
	L.reserve(V.size()-2);
	for(const auto& i : V)
	{
		if (i != source && i != drain)
			L.push_back(i);
		current[i] = i.begin();
	};
		
	auto it = L.begin();

	/////////////////algorithm////////////////////

	while (it != L.end())
	{
		if (discharge(current[*it],V[*it]))
		{
			swap(*it,L[0]);
			it = L.begin();
		};
		++it;
	};

};

int graph::_preFlow::operator()()// get max flow
{
	return overload[drain];
};