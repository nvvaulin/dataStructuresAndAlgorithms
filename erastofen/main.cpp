#include <vector>
#include <iostream>
#include <math.h>
using namespace std;

bool prost(int a)
{
	if (a<4) return 1;
	if (!(a%2)) return 0;
	int a1=(int)(sqrt((double)(a)));
	for  (int i=3;i<a1;i+=2)
		if (!(a%i)) return 0;
	return 1;
}
vector<int> eratosfen(int n)
{
	vector<int> a;
	int l=0;
	for (int i=2; i<n;i++)
	{
		unsigned int j;
		for(j=0; j<l;j++)
			if (i%a[j]==0) break;
		if (j==l) 
		{
			a.push_back(i);
			++l;
		};
	};
	return a;
}
void main()
{
	setlocale(LC_ALL,"Russian");
	int n;
	cin>>n;
	(prost(n))?cout<<n<<" Ч простое число\n" : cout<<n<<" Ч составное число\n";
	cout<<"простые числа до n:\n";
	vector<int> a=eratosfen(n);
	for(unsigned int i=0; i<a.size();i++)
		cout<<a[i]<<' ';
  cin.get();
}
	