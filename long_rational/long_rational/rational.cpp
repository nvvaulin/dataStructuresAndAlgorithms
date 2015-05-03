/*#include <vector.h>
using namespace std;

class rational
{
	vector<unsigned int> mantissa;
	int period;//кол-во чисел с конца
	int exp;//кол-во чисел с начала
	rational mul(rational);
	rational mul(int);
	rational sum(rational);
	rational sum(int);
	bool get_period();
	
};
int rational::get_period()
{
};
rational rational::mul(int x)
{
	rational res;
	res.exp=exp;
	int ost;
	_int64 temp = x*mantissa[0];
	int ost = temp % max;

	if (temp/max) 
	{
		res.exp++;	
		res.mantissa.push_back(temp/max);
	};

	for(int i = 1; i < mantissa.size(); ++i)
	{
		temp = x*mantissa[i] + ost;
		ost = temp % max;
		res.mantissa.push_back(temp/max);
	};

	temp = x*mantissa[mantissa.size() - period] + ost;
	ost = temp % max;
	res.mantissa.push_back(temp/max);
	res.get_period();

	return res;
};
	

	 
rational rational::sum(rational x)
{
	rational res;
	


*/