#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>
#define SNAN  std::numeric_limits<double>::signaling_NaN(); /* signaling NaN */
using namespace std;


class matrix
{
	vector< vector<double> > a;
public:
	static matrix NaM;// not a matrix
	static matrix fNaM();//init NaM
	
	unsigned int heigth;
	unsigned int length;
	matrix(unsigned int l=1,unsigned int h=1,double x=0);
	matrix(double x) { matrix(1,1,x);};
	vector<double>& operator[](const unsigned int& i) const;
	vector<double>& operator[](const unsigned int& i);
	matrix operator*(const double&)const;
	matrix operator/(const double)const;
	matrix operator*(const matrix&)const;
	matrix operator+(const matrix&)const;
	matrix operator-(const matrix&)const;
	matrix operator^(const size_t x)const;
	matrix& operator=(const matrix&);
	matrix transporate();	
	void insert(const matrix&,unsigned int x,unsigned int y);
	double det();

	void show(int n=1);//n - length of elements
	void one();//one-matrix
	void nil();//null-matrix
	
};