#include "kurskala.h"
#include <fstream>
#include <iostream>

void main()
{
	graph g;
	size_t N,M,w,a,b,W = 0;
	ifstream f("input.txt");
	f>>N>>M;
	while(N--)
	{
		f>>w;
		W+=w;
	};
	while(M--)
	{
		f>>a>>b>>w;
		g.insert(a,b,w);
	};

	cout<< g.weight(g.kurskala()) * W;

};