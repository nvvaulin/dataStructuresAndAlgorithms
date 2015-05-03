#include <iostream>
#include <memory>
#include <vector>
#include "UniversalHash.h"
using namespace std;

template<class T>
class eq
{
public:
	bool operator()(const T& x,const T& y)const
	{
		return x == y;
	};
};

template<class TK,class T, class Tequal = eq<TK>,class HF = UniversalHesh<TK> >
class qqhash
{
	struct _pair
	{
		T value;
		TK key;
		_pair(const TK& k,const T& v) : key(k),value(v) {};
		_pair(){};
	};
	Tequal equal;
	size_t cup;
	size_t max_cup;
	size_t min_cup;
	const static size_t min_count = 2;
	const static size_t max_count = 8;
	vector< vector<_pair> > data;
	vector< vector<bool> > is_value;
	vector<HF> hash;	
	void uniq_HF()
	{
		for(size_t i = 1; i < 2;++i)
		{
			HF temp(data[0].size());
			size_t j = 0;
			while(j < hash.size() )
			{
				if (temp == hash[j])
				{
					--i;
					break;
				};
				++j;
			}
			if (i==1)
				hash.push_back(temp);
		};
	};

	void swap(_pair& x,_pair& y)
	{
		_pair temp = x;
		x = y;
		y = temp;
	};
	

	void rebuild()
	{
		if (max_count > data.size())//insert new array
		{
			data.reserve(data.size()+1);
			data.push_back(vector<_pair>(data[0].size()));
			is_value.reserve(is_value.size()+1);
			is_value.push_back(vector<bool>(data[0].size(),false));
			uniq_HF();
			return;
		};
		qqhash<TK,T,Tequal,HF> temp(max_cup*8,min_cup*8);
		for(size_t i = 0;i < data.size();++i)
			for(size_t j = 0; j < data[i].size(); ++j)
				if(is_value[i][j])
					temp.insert(data[i][j].key,data[i][j].value);
		//*this = move (temp);
		cup = temp.cup;
		max_cup = temp.max_cup;
		min_cup = temp.min_cup;
		hash = move(temp.hash);
		data = move(temp.data);
		is_value = move(temp.is_value);
	};

	bool find(const TK& k, size_t& i,size_t& j) const
	{		
		j = 0, i = 0;
		while (i < data.size() )
		{
			j = hash[i](k);
			if (is_value[i][j])
				if (equal(k,data[i][j].key))
					return true;
			++i;
		};
		return false;
	};

public:
	qqhash(size_t _max_cup = 16,size_t _min_cup = 8) : max_cup(_max_cup), min_cup(_min_cup),
			data(min_count, vector<_pair>((_max_cup + (min_count>>2))/ min_count)),
		is_value(min_count, vector<bool> (((_max_cup + (min_count>>2))/ min_count),false))  
	{
		cup = 0;
		for(size_t i = 0; i < min_count;++i)
		{
			uniq_HF();
		};
	};

	T* find(const TK& k)
	{
		T* res;
		size_t i,j;
		if (find(k,i,j))
			return &data[i][j].value;
		else
			return 0;
	};

	bool del(TK k)
	{
		size_t i,j;
		if (find(k,i,j))
		{
			data[i][j].value.~T();
			data[i][j].value = T();
			is_value[i][j] = false;
			--cup;
			return true;
		};
		return false;
	}; 
	T operator[](const TK& k)const
	{
		T* res = find(k);
		if (res)
			return *res;
		else
			return T();
	};

	T& operator[](const TK& k)
	{
		insert(k,T());
		T* res = find(k);
		if (res)
			return *res;
	};

	void insert(const TK& k,const T& v)
	{
		size_t i,j;
		//if already in
		T* temp = find(k);
		if (temp)
		{
			*temp = v;
			return ;
		};

		size_t iter = 0;
		_pair p(k,v);
		size_t iter_max = data.size()*data[0].size();
		i = 0, j = hash[i](p.key);
		while(is_value[i][j])
		{
			swap(p,data[i][j]);
			++i;
			i %= data.size();
			j = hash[i](p.key);
			if(++iter == iter_max)
			{
				rebuild();
				insert(p.key,p.value);
				return;
			};

		};
		is_value[i][j] = true;
		data[i][j] = p;
		++cup;
	};

	size_t size()const
	{
		return cup;
	};
};


void main()
{
	qqhash<int,char> h;
	for(int i = 0; i<2555; ++i)
		h.insert(i,3);
	
	h.del(45);
};


