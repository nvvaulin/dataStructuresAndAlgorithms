#include <vector>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <time.h>
using namespace std;

size_t length(const char* s)
{
	size_t res = 0;
	while (s[res++]);
	return --res;
};

size_t length(int x)
{
	--x;
	char s[16];
	itoa(x,s,10);
	return length(s);
};

int* resize(int* v, size_t size, size_t prev_size = 0)
{
	int* res = new int [size];
	memcpy(res,v,((size > prev_size) ? prev_size : size)*sizeof(int));
	for(int i = prev_size; i < size; ++i)
		res[i] = 0;
	return res;
};

class long_integer
{
protected:
	friend int    euclid(long_integer _a,int b);

	long_integer& sum(const long_integer&);
	long_integer& minus(const long_integer& x,int order = 0);

	long_integer& mul(const int x);
	long_integer  mul(const long_integer& x) const;

	long_integer  div(int x,int& ost) const;
	long_integer  div(const long_integer& x, long_integer& ost) const;

	int			  mod(const int) const;
	long_integer  mod(const long_integer& x) const;
	
	int compareABS(const long_integer& x,int order = 0) const;//-1: |this| < |x|; 1: |this|>|x|; 0: |this| = |x|;
	int compare(const long_integer& x,int order = 0) const;//-1: this < x; 1: this>x; 0: this = x;
	
	void del_null();//delete 0 from the begin

	size_t size;
public:
	static const __int64 base = 1000000000;
	bool sign;
	int* value;

	void read(const char* s);
	char* write() const;

	long_integer(int x = 0)
	{
		value = new int;
		size = 1;
		*this = x;
	};
	long_integer(size_t _size,int v,bool _sign = true);

	long_integer(const long_integer& x)
	{
		sign = x.sign;
		value = new int [x.size];
		size = x.size;
		memcpy(value,x.value,size*sizeof(int));
	};

	long_integer operator*(const long_integer& x) const
	{
		return this->mul(x);
	};
	long_integer operator/(const long_integer& x) const
	{
		long_integer ost(0,0);
		return div(x,ost);
	};
	long_integer operator*(int x) const
	{
		long_integer res(*this);
		res.mul(x);
		return res;
	};
	long_integer operator/(int x) const
	{
		int ost;
		if (base > x)
			return div(x,ost);
		long_integer _x(x);
		return *this/_x;
	};
	long_integer operator%(const long_integer& x) const
	{
		return mod(x);
	};

	int operator%(int x) const
	{
		return mod(x);
	};

	long_integer& operator-=(const long_integer& x)
	{
		if (x.sign^sign)
		{
			sum(x);
			return *this;
		}
		else
			if (compareABS(x) ==1)
			{
				minus(x);
				return *this;
			}
			else
			{
				long_integer res(x);
				res.minus(*this);
				*this = res;
				return *this;
			};
	};

	long_integer operator-(const long_integer& x) const
	{
		long_integer res(*this);
		res -= x;
		return res;
	};

	long_integer& operator+=(const long_integer& x)
	{
		if (!(x.sign^sign))
		{
			sum(x);
			return *this;
		}
		else
			if (compareABS(x) ==1)
			{
				minus(x);
				return *this;
			}
			else
			{
				long_integer res(x);
				res.minus(*this);
				*this = res;
				return *this;
			};
	};
		
	long_integer operator+(const long_integer& x) const
	{
		long_integer res(*this);
		res -= x;
		return res;
	};

	bool operator>(const long_integer& x) const
	{
		return (compare(x) == 1);
	};
	bool operator<(const long_integer& x) const
	{
		return (compare(x) == -1);
	};
	bool operator==(const long_integer& x) const
	{
		return (!compare(x));
	};
	bool operator>=(const long_integer& x) const
	{
		return (compare(x) != -1);
	};
	bool operator<=(const long_integer& x) const
	{
		return (compare(x) != 1);
	};
	long_integer& operator*=(const long_integer& x)
	{
		*this = this->mul(x);
		return *this;
	};
	long_integer& operator/=(const long_integer& x) 
	{
		long_integer temp;
		*this = div(x,temp);
		return *this;
	};
	long_integer& operator=(int x)
	{
		sign = (x > 0);
		x = abs(x);
		size = 0;
		if (!x) 
		{
			value = resize(value,++size);
			value[0] = x;
		}
		else
			while (x)
			{
				int temp  = x / base;
				value = resize(value,(++size),size - 1);
				value[size - 1] = x - temp*base;
				x = temp;
			};
		return *this;
	};
	long_integer& operator=(const long_integer& x)
	{
		sign = x.sign;
		value = resize(value,x.size);
		size = x.size;
		memcpy(value,x.value,size*sizeof(int));
		return *this;
	};


	long_integer& operator*=(int x)
	{
		mul(x);
		return *this;
	};
	long_integer& operator/=(int x)
	{
		int ost;
		if (base > x)
			*this = div(x,ost);
		else
		{
		long_integer _x(x);
		*this/=_x;
		};
		return *this;
	};
	~long_integer()
	{
		if (value)
			delete[] (value);
	};
	long_integer operator^(int x)
	{
		long_integer res(1);
		if (*this < base)
		{
			int s = 1;
			int n = 0;
			while ((s < base) && (n++ <=x))
				s*=value[0];
			--n;
			s/=value[0];			
			for (int i = 0; i < x/n; ++i)
				res.mul(s);
			for (int i = 0; i < x%n; ++i)
				res.mul(value[0]);
			
		}
		else
		{
			for (int i = 0; i < x; ++i)
				res.mul(*this);
		};
		if (!sign) 
				res.sign = (x%2) ? true : false;
			else
				res.sign = true;
			return res;
	};

};


