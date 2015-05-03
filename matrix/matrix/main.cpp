#include "matrix.h"
void main()
{
	matrix a(5,5,1.23423);
	matrix b(1,1,0);
	b=a*3;
	double x=a[0][0];
	a=a*b;
	a.insert(b,1,4);
	a.show(5);
	cout<<a.det();
	cin.get();
}