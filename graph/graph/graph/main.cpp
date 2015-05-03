#include "graph.h"
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
	ifstream f("input.txt");
	int x,y;
	if (f)
		if (!f.eof())
			f>>x;
		else
			cin>>x;
	else
		cin>>x;
	graph g(x);
	if (f)
	{
		while(!f.eof())
		{
			char comand;
			f>>comand;
			switch (comand)
			{
				case '+' : 
					{
						f >> x >> y; 
						g.insert_edge(x,y); 
						break;
					};
				case '-' : 
					{
						f >> x >> y; 
						g.delete_edge(x,y); 
						break;
					};
				case 's' : 
					{
						f >> x >> y; 
						shared_ptr<char128> s(new char128);
						for(int i = 0; i < 128; ++i)
						f>>(*s).c[i]; 
						g.insert_word(x,y,s); 
						break;
					};
				case 'c' : 
					{
						f>> x >> y;
						g.delete_word(x,y);
						break;
					};
				case 'f' : 
					{
						auto edges = g.find_edges_of_sccg();				
						for( auto i : edges)
						{
							cout<<'/n';
							for(auto j : i)
								if(j.second)
									cout<<j.second<<'/n';
						};
						break;
					};
			};
		};
	};

	while(1)
	{
		char comand;
		cin>>comand;
		switch (comand)
		{
			case '+' : 
				{
					cin >> x >> y; 
					g.insert_edge(x,y); 
					break;
				};
			case '-' : 
				{
					cin >> x >> y; 
					g.delete_edge(x,y); 
					break;
				};
			case 's' : 
				{
				f >> x >> y; 
				shared_ptr<char128> s(new char128);
				for(int i = 0; i < 128; ++i)
				cin>>(*s).c[i]; 
				g.insert_word(x,y,s); 
				break;
				};
			case 'c' :
				{
					cin >> x >> y; g.delete_word(x,y); break;
				};
			case 'f' : 
				{
					auto edges = g.find_edges_of_sccg();				
					for( auto i : edges)
					{
						cout<<'/n';
						for(auto j : i)
							if(j.second)
								cout<<j.second->c<<'/n';
					};
					break;
				};
		};
	};
};

				

