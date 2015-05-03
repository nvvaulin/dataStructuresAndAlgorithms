//#include "long_integer.h"
//#include <iostream>
//#include <time.h>
//vector<int> mod_convert;
//long_integer mul_mod(1,1);
//vector<int> mod;
//bool NOD(int a,int b)
//{	
//	while (b&&a)
//		if (a > b)
//			a= (a%b);
//		else
//			b= (b%a);
//	return (a + b == 1);
//};
//
//class long_rational
//{
//public:
//	long_rational();
//	vector <int> dividend;
//	vector <int> divider;
//	
//	static const int l_mod = 512;
//	//static
//	//static 
//	static void create_mod();
//	long_rational(int);
//	void sum(vector <int>& x,const vector <int>& y);
//	void mul(vector <int>& x,vector <int>& y);
//	void sum(long_rational);
//	void mul(long_rational);
//	void div(long_rational);
//	long_integer decode(vector <int>);
//};
//
//void long_rational::create_mod()
//{
//	
//	mul_mod = 1;
//	
//	for (int i = 1000; i<10000; i++)
//	{
//		if (mod.size() >= l_mod)
//			break;
//		else
//			{
//				for (int j = 0; j<=mod.size(); j++)
//					if (j == mod.size()) 
//					{
//						mod.push_back(i);
//						break;
//					}
//					else
//						if (!NOD(i,mod[j]))
//							break;
//		};
//	};
//
//	for(int i = 0; i <l_mod; ++i)
//	{
//		mul_mod*=mod[i];
//	};
//	for(int i = 0; i < l_mod; ++i)
//	{
//		mod_convert.push_back(euclid(mul_mod/mod[i],mod[i]));//??????????????????????
//	};
//};
//
//long_integer long_rational::decode(vector <int> x)
//{
//	long_integer res(0,0);
//	long_integer t1;
//	for(int i = 0; i < l_mod; ++i)
//	{
//		t1 = mul_mod/mod[i];
//		t1 = t1*mod_convert[i];
//	t1 = (t1)*x[i];
//	res += t1;
//	};
//	return res % mul_mod;
//};
//
//long_rational::long_rational(int x)
//{
//	vector<int> temp(l_mod,1);
//	divider = temp;
//	dividend = temp;
//	for (int i = 0; i < l_mod; i++)
//	{
//		dividend[i] = x%mod[i];
//	}
//};
//
//void long_rational::sum(vector<int>& x,const vector<int>& y)
//{
//	for(size_t i = 0; i < l_mod; i++)
//	{
//		x[i] +=y[i];
//		x[i] %=mod[i];
//	};
//};
//
//void long_rational::mul(vector <int>& x,vector <int>& y)
//{
//	for(size_t i = 0; i < l_mod; i++)
//	{
//		x[i] *=y[i];
//		x[i] %=mod[i];
//	};
//
//};
//
//void long_rational::mul(long_rational x)
//{
//	mul(dividend,x.dividend);
//	mul(divider,x.divider);
//};
//
//
//void long_rational::sum(long_rational x)
//{
//	vector<int> temp = divider;
//	mul(dividend,x.divider);
//	mul(temp,x.dividend);
//	mul(divider,x.divider);
//	sum(dividend,temp);
//};
//
//void long_rational::div(long_rational x)
//{
//	mul(dividend,x.divider);
//	mul(divider,x.dividend);
//};
//
