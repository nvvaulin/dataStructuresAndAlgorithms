#include "AVLTree.h"
#include <set>
#include <stdio.h>
#include <time.h>
using namespace std;

void main()
{
	AVLTree<int> t;
	set<int> s;
	set<int> s2;
	srand(time(0));
		int j1 =0 ;
	for(int i = 0; i < 10000; ++i)
	{
		
		int j = rand() % 100000000;
		t.push(j);
		s.insert(j);
	};
	auto j = t.begin();
	for( auto i : s)
	{
		++j;
		
		
	};
};