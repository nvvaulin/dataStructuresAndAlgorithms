#pragma once
#include "DateTime.h"



char* Interval::write(char* mask) const
{
	long long int temp = seconds;
	char default_mask[] = "DD hh:mm:ss";
	if (!mask)
		mask = default_mask;
	char* res =(char*)malloc((length(mask)+1)*sizeof(char));
	memcpy(res,mask,(length(mask) + 1)*sizeof(char));
	
	char buf[32];
		
	size_t p = pos('D',mask);
	size_t l = pos_last('D',mask);
	if (p)
	{
		itoa(temp/day,buf,10);
		temp = temp % day;
		insert(buf,res,p,l);
	};
			
	p = pos('h',mask);
	l = pos_last('h',mask);
	if (p)
	{
		itoa(temp/hour,buf,10);
		temp = temp % hour;
		insert(buf,res,p,l);
	};		
	
	p = pos('m',mask);
	l = pos_last('m',mask);
	if (p)
	{
		itoa(temp/minute,buf,10);
		temp = temp % minute;
		insert(buf,res,p,l);
	};
		
	p = pos('s',mask);
	l = pos_last('s',mask);
	if (p)
	{
		itoa(temp,buf,10);
		insert(buf,res,p,l);
	};	
	return res;
	};

Interval::Interval(char* s, char* mask){
	DateTime t(s,mask);
	seconds = t.seconds;
};

void Interval::read(char* s, char* mask){
	DateTime t(s,mask);
	seconds = t.seconds;
};


ostream& operator<<(ostream& s, Interval d)
{
	s<<d.write();
	return s;
};

istream& operator>>(istream& s, Interval d)
{
	char c[32];
	s>>c;
	d.read(c);
	return s;
};