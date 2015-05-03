#include "matrix.h"
#include "det.cpp"
using namespace std;

matrix matrix::NaM=fNaM();// not a matrix

matrix matrix::fNaM()
{
	matrix b(1,1);
	b[0][0]=SNAN;
	return b;
};

matrix& matrix::operator=(const matrix& m)
{
	a=m.a;
	length=m.length;
	heigth=m.heigth;
	return *this;
};

matrix::matrix(unsigned int l,unsigned int h,double x)
{
	vector<double> b(h,x);
	for (unsigned int i=0;i<l;i++)
		a.push_back(b);
	heigth=h;
	length=l;
};


vector<double>& matrix::operator[](const unsigned int& i)
{
	if ( i<heigth) return this->a[i];
	else
		throw "out of bounds";
};

vector<double>& matrix::operator[](const unsigned int& i) const
{
	if ( i<heigth) return this->a[i];
	else
		return NaM.a[0];
};

matrix matrix::operator*(const double& x)const
{
	matrix b(length,heigth);
	for (unsigned int i=0;i<length;i++)
		for (unsigned int j=0;j<heigth;j++)
			b[i][j]=a[i][j]*x;
	return b;
};

matrix matrix::operator*(const matrix& m)const
{
	if (length==m.heigth)
	{
	matrix b(length,heigth,0);
	for (unsigned int i=0;i<heigth;i++)
		for (unsigned int j=0;j<m.length;j++)
			for (unsigned int i1=0;i1<length;i1++)
				b.a[j][i]=b.a[j][i]+a[i][i1]*m.a[j][i1];
	return b;
	}
	else
		return NaM;
};
matrix matrix::operator+(const matrix& m)const
{
	unsigned int l=(length>m.length)?length:m.length;
	unsigned int h=(heigth>m.heigth)?heigth:m.heigth;
	matrix b(l,h,0);
	for (unsigned int i=0;i<h;i++)
		for (unsigned int j=0;j<l;j++)
		{
			double x,y;
			x=((length>j)&&(heigth>i))?a[j][i]:0;
			y=((m.length>j)&&(m.heigth>i))?m.a[j][i]:0;
			b[j][i]=x+y;
		}
	return b;
};
matrix matrix::operator-(const matrix& m)const
{
	unsigned int l=(length>m.length)?length:m.length;
	unsigned int h=(heigth>m.heigth)?heigth:m.heigth;
	matrix b(l,h,0);
	for (unsigned int i=0;i<h;i++)
		for (unsigned int j=0;j<l;j++)
		{
			double x,y;
			x=((length>j)&&(heigth>i))?a[j][i]:0;
			y=((m.length>j)&&(m.heigth>i))?m.a[j][i]:0;
			b[j][i]=x-y;
		}
	return b;
};
matrix matrix::transporate()
{
	matrix b(heigth,length);
	for(unsigned int i=0;i<heigth;i++)
		for(unsigned int j=0;j<length;j++)
			b[i][j]=a[j][i];
	return b;
};

void matrix::show(int n)
{
	for(unsigned int i=0; i<length;i++)
	{
		for(unsigned int j=0; j<heigth;j++)
		{
			cout.width(n+1);
			cout<<a[i][j]<<' ';
		};
		cout<<'\n';
	}
};
double matrix::det()
{
	if (length==heigth)
		return get_det(a);
	else
		return SNAN;
};
void matrix::insert(const matrix& m,unsigned int x,unsigned int y)
{
	x--;
	y--;
	unsigned int l=(length>m.length+x)?length:m.length+x;
	unsigned int h=(heigth>m.heigth+y)?heigth:m.heigth+y;
	matrix b(l,h,0);
	for (unsigned int i=0;i<length;i++)
		for (unsigned int j=0;j<heigth;j++)
			b.a[i][j]=a[i][j];
	for (unsigned int i=x;i<l;i++)
		for (unsigned int j=y;j<h;j++)
			b.a[i][j]=m.a[i-x][j-y];
	a=b.a;
	length=l;
	heigth=h;
};

void matrix::one()
{
	for(int i=0;i<length;++i)
		for (int j = 0; j<heigth; ++j)
			a[i][j] = (i==j) ? 1 : 0;
};
void matrix::nil()
{
	for(int i=0;i<length;++i)
		for (int j = 0; j<heigth; ++j)
			a[i][j] = 0;
};

matrix matrix::operator/(const double x)const
{
	matrix res = *this;
	for(int i=0;i<length;++i)
		for (int j = 0; j<heigth; ++j)
			res.a[i][j] = res.a[i][j]/x;
	return res;
};

matrix matrix::operator^(const size_t x)const
{
	matrix res = *this;
	if (x==0)
		res.one();
	else	
		for(int i = 0; i<x; ++i)
			res = res*(*this);
	return res;
};


matrix operator*(int x,matrix m)
{
	return m*x;
}