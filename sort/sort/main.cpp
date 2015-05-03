#include "sort.h"

#include <fstream>
#include <intrin.h>
#define MAXARR 100
#define ITERARR 10
#define ITER 1
#define TOBS 20
#define ITER_TOBS 1


int compare(void* x,void* y)
{	
	int i = *((int*)(x));
	int j = *((int*)(y));
	if (*((int*)(x)) < *((int*)(y))) return -1;
	if (*((int*)(x)) > *((int*)(y))) return 1;
	return 0;
};


void main()
{
	int a[MAXARR], aq[MAXARR], ab[MAXARR][2];
	size_t atobs[TOBS];
	unsigned __int64 t;
	unsigned __int64 tq = 0;
	unsigned __int64 tb = 0;
		
	for (size_t tobs = TOBS; tobs < ITER_TOBS+TOBS; tobs++)
	{
		for (int k = 0; k < ITERARR; k++)
		{
			srand(time(0));

			for (int i = 0; i < 10; i++)
				a[i] = rand() % 1000000;

			for (int i = 0; i < ITER; i++)
			{		
				memcpy(ab,a,sizeof(int) * MAXARR);
				memcpy(aq,a,sizeof(int) * MAXARR);

				unsigned __int64 t;

				t = __rdtsc();  

				qSort(a,0,MAXARR,sizeof(int),&compare,tobs);

				tq += __rdtsc() - t;

				size_t l = 0;
				size_t h = MAXARR;
				t = __rdtsc();  

				bubbleSort((char*)a,l,h,sizeof(int),&compare);

				tb += __rdtsc() - t;
			};
		};

		std::cout<<	tobs<<' '<<((double)(tb))/((double)(tq))<<'\n';
	};
	
	std::cin>>a[1];

};



