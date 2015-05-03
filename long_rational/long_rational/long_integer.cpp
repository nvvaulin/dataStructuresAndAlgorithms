#include "long_integer.h"


void long_integer::del_null()
{
	size_t prev_size = size;
	while ((!value[size-1])&&(size>1))
	--size;
value = resize(value,size,prev_size);
};

long_integer::long_integer(size_t _size,int v,bool _sign)
{
	size = _size;
	if (_size)
	{
		value = new int [size];
		for(int i = 0; i < size; ++i)
			value[i] = v;
	}
	else
		value = 0;
	sign = _sign;
};

int long_integer::compareABS(const long_integer& x,int order) const//-1: this < x; 1: this>x; 0: this = x;
{
	int res;
	if (size-order > x.size)
		return 1;
	if (size-order < x.size)
		return -1;

	int i = size - order;
	do
	{
		--i;
		if (value[i + order] != x.value[i])
			break;
	}
	while(i);

	if (value[i+order] == x.value[i])
		res =  0;
	if (value[i+order] > x.value[i])
		res = 1;
	else
		res = -1;
	return res;
};

int long_integer::compare(const long_integer& x,int order) const//-1: this < x; 1: this>x; 0: this = x;
{
	if ((size == 1)&&(x.size == 1)&&(!value[0])&&(!x.value[0])&&!order)
		return 0;
	if (sign^x.sign)
		return (sign) ? 1 : -1;
	int k = (sign) ? 1 : -1;
	return compareABS(x,order)*k;
};

long_integer& long_integer::sum(const long_integer& x)
{

	value = resize(value,((size > x.size) ? size : x.size)+1,size);

	__int64 r = 0;
	for(size_t i = 0; i < x.size; ++i)
	{
		__int64 temp = value[i] + x.value[i] + r;
		r = temp / base;
		value[i] = temp - base*r;
	};
	size = (size > x.size) ? size : x.size;
	if (r)
		value[size++] = r;
	return *this;
};

long_integer& long_integer::minus(const long_integer& x,int order)//|this| > |x|  !!
{
	__int64 temp = 0;
	
	for(size_t i = 0; i < x.size; ++i)
	{
		temp = value[i + order] - x.value[i];
		if (temp < 0)
		{
			temp += base;
			--value[i+1 + order];
		};

		value[i + order] = temp;
	};

	del_null();
	return *this;
};

long_integer& long_integer::mul(int _x)
{
	sign = !(sign^(_x > 0));
	if (!_x)
	{
		value = resize(value,1);
		value[0] = 0;
		size = 1;
		return *this;
	};
	_x = abs(_x);
	if (_x==1)
		return *this;

	__int64 temp = 0;
	__int64 x = (__int64)_x;
	__int64 r = 0;

	for (size_t i = 0; i < size; ++i)
	{
		temp = r + (__int64)value[i]*x;
		r = temp / base;
		value[i] = temp - base*r;
	};

	if (r)
	{
		value = (int*) resize(value,(++size),size-1);
		value[size-1] = r;
		
	};
	return *this;

};

long_integer long_integer::mul(const long_integer& x) const
{

	long_integer res(size+x.size,0);
	for (size_t i=0; i<size; ++i)
	{
		__int64 temp = 0;
			for (size_t j=0; j < (x.size) || temp; ++j)
		{
			__int64 r = (__int64)res.value[i+j] + (__int64)value[i] * (j < x.size ? (__int64)x.value[j] : 0) + temp;
			temp =  r / base;
			res.value[i+j] = int (r - base*temp);
		};
	};

	res.del_null();
	res.sign = !(sign^x.sign);
	return res;
};


long_integer long_integer::div(int _x,int& ost) const
{
	long_integer res(size,0);
	res.sign = !(sign^(_x > 0));
	_x = abs(_x);
	if ((size == 1) && !value[0]) return res;
    if ((size == 1) && (_x == 1))
    {
        res = *this;
        res.sign = !(sign^(_x > 0));
        return res;
    };
	__int64 x = (__int64)_x;
	__int64 temp = 0;
	__int64 r = 0;
	size_t i = size;
	do
	{
		temp = ((__int64)(value[--i]) + (__int64)(temp - x*r) * (__int64)base);
		r = temp / x;
		res.value[i] = r;
	}
	while (i) ;

	res.del_null();

	ost = (sign) ? r : -r;

	return res;
};


long_integer long_integer::div(const long_integer& x,long_integer& ost) const
{
	if (compareABS(x) == -1)
	{
		long_integer res(1,0);
		ost = *this;
		return res;
	};
	long_integer res(0,0);
	res.value = new int [size];
	res.sign = !(sign^x.sign);
	long_integer temp(*this);

	while(temp.compareABS(x) > -1)
	{
		int order;
		__int64 hight_order;
//выдел€ю подчисло
		if (temp.compareABS(x,temp.size - x.size) > -1)
		{
			order = temp.size - x.size;
			hight_order  = temp.value[temp.size - 1];
		}
		else
		{
			order = temp.size - x.size - 1;
			hight_order  = temp.value[temp.size - 1]*base + temp.value[temp.size - 2];
		};
		//bin search
		int min, max, mid;
		min = 1;
		max = hight_order /(x.value[x.size - 1]);
		long_integer m = x;
		m.mul(max);
		if (temp.compareABS(m,order) == -1)//немного снизит множитель
			do
			{
				int mid = (max + min) / 2;
				m = x;
				m.mul(mid);
				int c = temp.compareABS(m,order);
				if (!c)
					min = max = mid;
				if (c == 1)
					min = mid;
				else
					max = mid;

			}
			while ( max - min > 1);
		else
			min = max;

		m = x;
		m.mul(min);
		temp.minus(m,order);
		res.value[res.size] = min;
		++res.size;
	};
	ost = temp;
	delete [] (temp.value);
	temp.value = new int[res.size];
	temp.size = 0;
	int i = res.size;
	while (i--)
		temp.value[temp.size++] = res.value[i];

	return temp;
};

long_integer long_integer::mod(const long_integer& x) const
{
	long_integer res(0,0);
	div(x,res);
	return res;
};

int long_integer::mod(int _x) const
{

	if ((size < 2)&&(!value[0])) return 0;
	__int64 x = (__int64) abs(_x);
	__int64 temp = 0;
	size_t i =size;
	do
	{
		temp = (__int64)value[--i] + (temp % x) * base;
	}
	while (i) ;
	if (!sign)
		temp = -temp;
	return temp % _x;
};

int euclid(long_integer _a,int b)
{
	int r, x1, x2, x,a;
	a = b;
	_a.div(b,b);
	x = 1;
	x2 = 0;
	x1 = 1;

	while (b > 0)
	{
		r = a % b;
		x = x2 - (a/b) * x1;
		a = b;
		b = r;
		x2 = x1;
		x1 = x;
	};
	return x2;
};

void long_integer::read(const char* s)
{
	if (s[0] == '-') 
	{
		sign = false;
		++s;
	}
	else
		sign = true;
	if (s[0] == '+')
		++s;
	size_t i = length(s);
	size_t len = i;
	int l_base = length(base);
	value = resize(value,(len-1)/l_base + 1,size);
	
	char temp[16];
	while (i)
	{
		size_t l = 0;
		for(size_t j = (i > l_base) ? i-l_base : 0; j < i; ++j)
			temp[l++] = s[j];
		temp[l] = 0;
		value[(len - i)/l_base] = atoi(temp);
		i = (i > l_base) ? (i - l_base) : 0;
	};
	
	size = (len-1) / l_base+1;
};

char* long_integer::write() const
{
	size_t l_base = length(base);
	char* res = new char [l_base*size + 1];
	char* s = res;
	if (!sign)
		s++[0] = '-';
	size_t i = size;
	do
	{
		char buf[16];
		itoa(value[--i],buf,10);
		size_t j =(i != size - 1) ? l_base - length(buf) : 0;
		while (j)
			s++[0] = '0', --j;
		while (buf[j])
			s++[0] = buf[j++];		
	}while (i);
	s[0] = 0;
	return res;
};

void main()
{
	long_integer b;
	b.read("900123456200000000");
	long_integer a;
	a.read("13456111111111");
	b*=a;
	cout<<b.write();
	return ;
};
