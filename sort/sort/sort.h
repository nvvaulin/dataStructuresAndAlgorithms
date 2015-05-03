#include <time.h>
#include <iostream>

inline void swap(char *x,char *y,const size_t &size)
{
	char temp;

	for (size_t i = 0; i < size; i++) 
	{
		temp = x[i];
		x[i] = y[i];
		y[i] = temp;
	};
};

void bubbleSort(char* a, size_t &l, size_t &h, const size_t &size, int (*compare)(void* x,void* y) )
{
	for (size_t i = l; i < h-size; i += size) 
		for (size_t j = i + size; j < h; j += size) 
			if (compare(a+i,a+j) == 1) swap(a+i,a+j,size);
};

void sort(char* a, size_t &l, size_t &h, const size_t &size, int (*compare)(void* x,void* y), size_t &tobs )
{
	if ((l+h)<tobs) 
	{
		bubbleSort(a,l,h,size,compare);
		return ;
	};

	size_t r = rand()%(h-l);
	r = size*(r/size);
	while ((r==0)||(r==h-l))
		r = rand()%(h-l);
	r += l;

	size_t i = h;
	size_t j = l;
	int tt = (int)(a[i]);
	do 
	{		
		while (compare(&a[i],&a[r]) == 1) i -= size;		
		while (compare(&a[j],&a[r]) ==-1) j += size;
		if (i >= j)
		{
			swap(&a[j],&a[i],size);
			i -= size;
			j += size;
		};
	}
	while (i > j);

	if(l < i) sort(a, l, i, size,compare, tobs);
    if(j < h) sort(a, j, h, size,compare, tobs);
  };


void qSort(void* a, size_t l, size_t h, size_t size, int (*compare)(void* x,void* y), size_t tobs )
{
	srand(time(0));
	l *= size;
	h *= size;
	tobs *= size;
	sort((char*)(a),l,h,size,compare, tobs);
};
