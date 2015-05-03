#include "header.h"

void main()
{
	char a[250],b[50];
	cin>>a;
	cin>>b;
	str_array c=split(a,b);
	for (unsigned int i=0;i<c.l;i++)	
		cout<<c.c[i]<<'\n';
	 delete_string_array(c);
	getch();

}