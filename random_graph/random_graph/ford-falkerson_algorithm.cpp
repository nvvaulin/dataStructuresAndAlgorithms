#include "graph.h"




vector<graph::vertex_id> graph::get_path(vertex_id a,vertex_id b)
	{
		stack<pair<vertex_id,size_t> > s_dfs;//pair<id vertex,point where you came from>
		vector<COLOR> color(V.size(),WHITE); 
		s_dfs.push(make_pair(a,a));
		color[a] = BLACK;

		while(!s_dfs.empty())
		{
			vertex_id n = s_dfs.top().first;

			if (n == b)//it right way so we find solution
			{
				vector<vertex_id> res(1,n);
				n = s_dfs.top().second;
				do
				{								
					while (s_dfs.top().first != n)
						s_dfs.pop();							
					res.push_back(n);
					n = s_dfs.top().second;
					s_dfs.pop();
				}while (!s_dfs.empty());
				return res;
			};
			
			//simple dfs			
			bool go_out = true;
			for(const auto& i : V[n])
				if (color[i.first] == WHITE)
				{
					color[i.first] = GRAY;
					s_dfs.push(make_pair(i.first,n));
					go_out = false;
				};

			if(go_out)//all childs is not white  remove n from stack
			{
				color[n] = BLACK;
				s_dfs.pop();
			};
					
		};
		return vector<vertex_id>();//we find nothing
	};


	int graph::ford_falkerson(vertex_id a,vertex_id b)
	{
		vector<vertex_id> path = get_path(a,b);
		if (path.empty())
			return -1;//no paths
		size_t res = 0;
		do
		{
			size_t m = *min_element(path.begin(),path.end());
			for(size_t i = 0; i+1 < path.size(); ++i)
				if(m >= V[path[i]][path[i+1]])
					delete_edge(path[i],path[i+1]);
				else
					V[path[i]][path[i+1]] -= m;
			res += m;
			path = get_path(a,b);
		}while(!path.empty());
		return res;
	};