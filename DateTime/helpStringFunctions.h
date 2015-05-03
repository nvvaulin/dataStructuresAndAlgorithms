//Functions which helps to work with strings

size_t length(char* s)
{
	int i = 0;
	while (s[i++]);
	return --i;
};

//position of first synbol c in s
size_t pos(char c,char* s)
{
	size_t res = 0;
	while (s[res] != c)
		if (!s[res++])
			return 0;
	return ++res;
};


//position of last synbol c in s
size_t pos_last(char c,char* s)
{
	size_t res = length(s) - 1;
	while (s[res] != c)
		if (!res--)
			return 0;
	return ++res;
};


//insert buf which length must be l (if not then put 0 in the begin of buf) in res to position p 
void insert(char* buf, char* res, size_t p, size_t l)
{
	size_t len = length(buf);
	size_t i = 0;
	--p;
	do
	{
		res[p++] = (len < l-p) ? '0' : buf[i++];
	}while( p < l);
};