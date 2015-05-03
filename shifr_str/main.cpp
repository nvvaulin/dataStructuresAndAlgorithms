#include <iostream>
#include <conio.h>
using namespace std;




void print_bytes(const void *mem, int size)
{
	char* p=(char*)mem;
	for(int i=0;i<size;i++)
	{
		char temp=*p;
		for (int j=0; j<8; j++)
		{
			char b=0x7F;			
			cout<<((b|temp)!=b);
			temp<<=1;
		}
		p++;
		cout<<' ';
	}
};
void main()
{
	double n;
	cin>>n;	
	print_bytes(&n,sizeof(n));
	getch();
};

