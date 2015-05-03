#include <conio.h>
#include <iostream>
#include <iomanip>
using namespace std;

long double KahanSum(int n)
{
    long double sum=0.0;
    long double c=0.0;
	long double x,temp;
    for(int i=0; i<n; i++)
	{
		cin>>x;
		if(cin.fail())
       {
		    cout<<"input error\n";
		   	i--;
			cin.clear();
		    cin.ignore( cin.rdbuf()->in_avail());
       }
		else
		{
			x-=c;
			temp=sum+x;        
			c=(temp-sum)-x;   
			sum=temp;
		}
	}
    return sum;
}
void main()
{
	int n;
	cin>>n;
	cout<<fixed << setprecision(15) <<KahanSum(n);
	getch();
}