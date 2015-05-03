#include <string>
#include <iostream>
#include <vector>
#include <math.h>
#include "deque.h"
#include "bin_tree.h"
using namespace std;

struct str_func
{
	str_func(string a,double (*b)(double,...),int c);
	string s;
	double (*f)(double,...);
	int length;
};
str_func::str_func(string a,double (*b)(double,...),int c)
{
	s=a;
	f=b;
	length=c;
};

int compare(str_func elem1,str_func elem2)
{
	if (elem1.s == elem2.s) return 0;
	if (elem1.s > elem2.s) return 1 ;
		else
			return -1;
};

struct func
{
	double d;
	double (* f) (double, ...);
	int length;
}
class polynom
{
	tree<str_func> setfunc ;
	
	deque<func> create(string s)
};

void polynom::create_setfunc()
{
	tree<str_func> setfunc(&compare); 

	str_func s( "sin" ,&sin,1);
	setfunc.insert(s);
	free(&s);

	str_func s("cos" ,&cos,1);
	setfunc.insert(s);
	free(&s);

	str_func s("tg" ,&tan,1);
	setfunc.insert(s);
	free(&s);
	
	str_func s("*" ,&mul,1);
	setfunc.insert(s);
	free(&s);
};

deque<func> polynom::create(string s)
{
	deque<func>  result;
	int i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '(') 
		{
			i++;
			int j = i;
			while (s[i] != ')')
				i++;
			result.begin<<(create( s.substr( j ,i - j) ));
		}
		else
		{
			if set_fun.get(s[i]).s=