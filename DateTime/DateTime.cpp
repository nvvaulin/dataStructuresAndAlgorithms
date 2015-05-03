#include "DateTime.h"





ostream& operator<<(ostream& s, DateTime d)
{
	s<<d.write();
	return s;
};

istream& operator>>(istream& s, DateTime d)
{
	char c[32];
	s>>c;
	d.read(c);
	return s;
};



void DateTime::add_mouth(size_t x)
{
	switch (x)
	{
		case 1 : seconds+=0;  return ;
		case 2 : seconds+= 31*day; return ;
		case 3 : seconds+=((visocos()) ? 60*day : 59*day);  return ;
		case 4 : seconds+= ((visocos()) ? 91*day : 90*day);  return ;
		case 5 : seconds+= ((visocos()) ? 121*day : 120*day);  return ;
		case 6 : seconds+= ((visocos()) ? 152*day : 151*day);  return ;
		case 7 : seconds+= ((visocos()) ? 182*day : 181*day);  return ;
		case 8 : seconds+= ((visocos()) ? 213*day : 212*day);  return ;
		case 9 : seconds+= ((visocos()) ? 244*day : 243*day);  return ;
		case 10 : seconds+= ((visocos()) ? 274*day : 273*day); return ;
		case 11 : seconds+= ((visocos()) ? 305*day : 304*day); return ;
		case 12 : seconds+= ((visocos()) ? 335*day : 334*day); return ;
	};
};

size_t DateTime::get_mouth(size_t& _day) const
{
	
	_day = seconds/day - (get_year()*year)/day + 1;
	int i = 1;
	if (_day < 32)
		return i;
	_day -= 31;
	++i;
	if (_day < ((visocos() ) ? 30 : 29))
		return i;
	_day -= ((visocos() ) ? 29 : 28);
	int t = 8;
	++i;
	while (i < 13)
	{	
		while (i < t)
		{
			if (_day < 32)
				return i;
			_day -= 31;
			++i;
			if (i>=t)
				break;
			if (_day < 31)
				return i;
			_day -= 30;
			++i;
		};
		t = 13;
	};

};

DateTime::DateTime(char* s,char* mask)
{
	char default_mask[] = "YYYY.MM.DD hh:mm:ss";
	seconds = 0;
	if (!mask)
		mask = default_mask;
	
	size_t p = pos('Y',mask);
	if (p)
		add_year(atoi(s+p-1));
	p = pos('M',mask);
	if (p)
		add_mouth(atoi(s+p-1));
	p = pos('D',mask);
	if (p)
		add_day(atoi(s+p-1)-1);
	p = pos('h',mask);
	if (p)
		add_hour(atoi(s+p-1));
	p = pos('m',mask);
	if (p)
		add_minute(atoi(s+p-1));
	p = pos('s',mask);
	if (p)
		seconds += atoi(s+p-1);
};



char* DateTime::write(char* mask) const
{
	char default_mask[] = "YYYY.MM.DD hh:mm:ss";
	if (!mask)
		mask = default_mask;
	char* res =(char*)malloc((length(mask)+1)*sizeof(char));
	memcpy(res,mask,(length(mask) + 1)*sizeof(char));
	
	char buf[8];

	size_t p = pos('Y',mask);
	size_t l = pos_last('Y',mask);
	if (p)
		itoa(get_year(),buf,10);
	insert(buf,res,p,l);

	p = pos('M',mask);
	l = pos_last('M',mask);
	size_t _day;
	if (p)
		itoa(get_mouth(_day),buf,10);
	insert(buf,res,p,l);
	
	p = pos('D',mask);
	l = pos_last('D',mask);
	if (p)
		itoa(_day,buf,10);
	insert(buf,res,p,l);
	
	p = pos('h',mask);
	l = pos_last('h',mask);
	if (p)
		itoa(get_hour(),buf,10);
	insert(buf,res,p,l);
	
	p = pos('m',mask);
	l = pos_last('m',mask);
	if (p)
		itoa(get_minute(),buf,10);
	insert(buf,res,p,l);

	p = pos('s',mask);
	l = pos_last('s',mask);
	if (p)
		itoa(get_second(),buf,10);
	insert(buf,res,p,l);
	
	return res;
};
	

void main()
{
	DateTime t("0300.02.29");
	t.now();
	
	std::cout<<t;
}
