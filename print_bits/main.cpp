#include <iostream>
#include <conio.h>
#include <vector>
using namespace std;



struct byte
{
	unsigned b0:1;
	unsigned b1:1;
	unsigned b2:1;
	unsigned b3:1;
	unsigned b4:1;
	unsigned b5:1;
	unsigned b6:1;
	unsigned b7:1;
};


vector<char> print_bytes(const void *mem, int size)
{
	vector<char> a(8*size,0);
	int k=0; 
	char* p = (char*)mem;
	for(int i = 0; i < size; i++)
	{
		char temp = *p;
		for (int j = 0; j < 8; j++)
		{
			char b=0x7F;			
			cout<<((b|temp)!=b);
			a[j+8*(size-i-1)]=((b|temp)!=b) ? '1' : '0';
			temp<<=1;
		}
		p++;
		k++;
		cout<<' ';
	}
	return a;
};
void main()
{
	double n;
	cout<<"input double: ";
	cin>>n;

	vector<char> a=print_bytes(&n,sizeof(n));

	cout<<"\nsign = "<<a[0]<<"\nexp = ";

	for (int i = 1; i<12; i++)
		cout<<a[i];

	cout<<"\nmantiss = ";

	for (int i = 12; i<64; i++)
		cout<<a[i];

	cout<<'\n';
	byte* c=(byte*)(&n);
	for( int i=0; i<12;i++)
	{
		cout<<c->b0
			<<c->b1
			<<c->b2
			<<c->b3
			<<c->b4
			<<c->b5
			<<c->b6
			<<c->b7			
			<<' ';
		c++;
	};

	getch();
};

