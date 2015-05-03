#pragma once
#include "helpStringFunctions.h"
#include <iostream>
#include <time.h>
using namespace std;


class Interval
{
	long long int seconds;
	//time spends in seconds
	const static long long int year = 31472292;//astronomic year
	const static long long int day = 86400;//24*60*60
	const static long long int hour = 3600;
	const static long long int minute = 60;

public:
	Interval(long long int s = 0) : seconds(s) {};
	Interval(char* s, char* mask = 0);

	char* write(char* mask = 0) const;

	operator long long int ()const{
		return seconds;
	}

	long long int Seconds()const{
		return seconds;
	}

	long long int Minute()const{
		return seconds/minute;
	}

	long long int Hour()const{
		return seconds/hour;
	}

	void read(char* s, char* mask = 0);

};



class DateTime 
{
	long long int seconds;
	const static long long int year = 31472292;
	const static long long int day = 86400;
	const static long long int hour = 3600;
	const static long long int minute = 60;
	void add_year(size_t x){
		seconds += ((x*year) / day)*day;
	};
	void add_mouth(size_t x);	
public:
	bool visocos() const{
		size_t res = get_year();
		return (( (!(res % 4))&&(res % 100) ) || (!(res % 400)));
	};

	size_t get_year() const{//year rounded in down
		return ((seconds/day)*day + year/2) / year;
	};

	size_t get_mouth(size_t& _day) const;
	size_t get_day() const{
		size_t res;
		get_mouth(res);	
		return res;
	};

	size_t get_hour() const{
		return (seconds % day) / hour;
	};

	size_t get_minute() const{
		return (seconds % hour) / minute;
	};

	size_t get_second() const{
		return seconds % minute;
	};
	

	void add_day(size_t x){
		seconds+= x * day;
	};
	void add_hour(size_t x){
		seconds+= x * hour;
	};
	void add_minute(size_t x){
		seconds+= x * minute;
	};
	DateTime(char* s,char* _mask = 0);
	DateTime(long long int x = 0)
	{
		seconds = x;
	};
	char* write(char* x = 0) const;
	void read(char* c){
		DateTime temp(c);
		*this = c;
	};
	void now(){
		seconds = 0;
		add_year(1970);
		seconds += time(0)-3700800;//I don't know why!! But it works just with this string
	};

	Interval operator-(const DateTime& x) const
	{
		return seconds - x.seconds;
	};

	DateTime operator+(Interval x) const{
		DateTime res(*this);
		res.seconds += x;
		return res;
	};

	DateTime operator-(Interval x) const{
		DateTime res(*this);
		res.seconds -= x;
		return res;
	};

	DateTime& operator+=(Interval x){
		seconds+=x;
		return *this;
	};

	DateTime& operator-=(Interval x){
		seconds-=x;
		return *this;
	};

	bool operator>(const DateTime& x) const{
		return seconds>x.seconds;
	};
	bool operator<(const DateTime& x) const{
		return seconds<x.seconds;
	};
	bool operator==(const DateTime& x) const{
		return seconds==x.seconds;
	};

};
