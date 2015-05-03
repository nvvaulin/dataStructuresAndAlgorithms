#pragma once
#include <vector>
#include <time.h>
using namespace std;


template<class T>
class UniversalHesh
{
	size_t count;
	const static size_t size_word  = 1;
	vector<size_t> factor;
public:
	size_t get_count()
	{
		return count;
	};

	void generate()
	{
		srand(time(0)*rand());
		for(size_t i = 0; i < factor.size(); ++i)
			factor[i] = ( 1 + (rand() % (count>>2)) )*( (count>>2) + (rand() % (count>>2)) ) + rand() % 2;
	};

	UniversalHesh(size_t _count) : count(_count), factor(sizeof(T)+1)
	{
		generate();
	};

	bool operator==(UniversalHesh& x)
	{
		if (factor.size() != x.factor.size())
			return false ;
		for(size_t i = 0; i < factor.size(); ++i)
			if (factor[i] != x.factor[i]) return false;
		return true;
	};

	size_t operator() (const T& x) const
	{
		__int64 res = factor[0];
		char* c =(char*)&x;
		
		for (size_t i = 0; i < sizeof(T); ++i)
		{
			res += factor[i+1]*(c[i]+c[sizeof(T)-i-1]);
		};
		return res % count;
	};
};