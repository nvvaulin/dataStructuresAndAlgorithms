#include "graph.h"

vector< unordered_set<size_t> > graph::find_sccg() const
{
	vector< unordered_set<size_t> > sccg;//strongly connected component of the graph
	vector<size_t> in(vertexes.size(),0);
	vector<size_t> low(vertexes.size(),0);
	vector<COLOR> color(vertexes.size(),WHITE);
	size_t t = 0;
	size_t pref_low = ULONG_MAX;
	stack<size_t> s_dfs;

	//find strongly connected component of the graph
	for(auto i : vertexes)
	{
		if(!in[i.n])
		{
            low[i.n] = in[i.n] = ++t;
			s_dfs.push(i.n);
			while (!s_dfs.empty())
			{
				size_t k = s_dfs.top();

				if(color[k] == WHITE)
				{
					color[k] = GRAY;
					for( auto j : vertexes[k].edges)						
						if (!in[j.first])//if k is white
						{
							low[j.first] = in[j.first] = ++t;
							s_dfs.push(j.first);
						};
				}
                else//if k is gray
				{
					for( auto j : vertexes[k].edges)		
					{
						if(in[j.first] <  low[k] && color[j.first] != BLACK)//find path to previous vertex
								low[k] = in[j.first];
					};

					color[k] = BLACK;					
					s_dfs.pop();

                    if (!s_dfs.empty())
                        if(low[s_dfs.top()] > low[k])//if s_dfs.top in this group too
                            low[s_dfs.top()] = low[k];

                    if (sccg.size() && pref_low == low[k])//insert to the last group
							sccg.back().insert(k);
                    else//new group
					{
						pref_low = low[k];
                        sccg.push_back(unordered_set<size_t>());
						sccg.back().insert(k);
					};
                };
			};
		};
	};
	return sccg;
};

vector< vector< pair<pair<size_t,size_t>, shared_ptr<char128> > > > graph::find_edges_of_sccg() const
{
	auto sccg = find_sccg();
	vector< vector< pair<pair<size_t,size_t>, shared_ptr<char128> > > > res(1);
	size_t pref_group = ULONG_MAX;
	//find edges of strongly connected component of the graph (sccg)
	//res[0] - edges which are not in a sccg
	for(size_t group = 0; group < sccg.size(); ++group)

		for(auto vert_of_group : sccg[group])

			for(auto j : vertexes[vert_of_group].edges)

				if (sccg[group].find(j.first) != sccg[group].end() )//if edge connect vertexes of the group
				{
					if(pref_group != group)
					{
						pref_group = group;
						res.push_back(vector< pair<pair<size_t,size_t>, shared_ptr<char128> > >());
					};
					res.back().push_back(make_pair(make_pair(vertexes[vert_of_group].n,j.first),j.second) );
				}
				else
					res[0].push_back(make_pair(make_pair(vertexes[vert_of_group].n,j.first),j.second) );
	return res;
};