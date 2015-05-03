#include "header.h"


str_array split(const char *str, const char *delim)
{
	int MAX=64;
	int dMAX=64;
	char** arr=(char**)(malloc(MAX*sizeof(char*)));
	int prev=0;
	int k=0;
	int i=0;
	while (str[i]!='\0')
	{
		int j=0;
		while ((str[i+j]==delim[j])&&(delim[j]!='\0'))
			j++;
		if (delim[j]=='\0')
		{
			arr[k]=(char*)(malloc(i-prev+1));
			for(int l=0;l<i-prev;l++)
			{
				arr[k][l]=str[prev+l];
			}
			arr[k][i-prev]='\0';
			k++;
			if (MAX<=k) 
			{
					MAX+=dMAX;
					arr=(char**)realloc(arr,MAX*sizeof(char*));
			}
			prev=i=i+j;
			i--;
			
		}
		i++;
	}
	arr[k]=(char*)(malloc(i-prev+1));
	for(int l=0;l<i-prev;l++)
	{
		arr[k][l]=str[prev+l];
	}
	arr[k][i-prev]='\0';
	k++;
	arr[k]=(char*)(malloc(1));
	arr[k][0]='\0';
	str_array arr1;
	arr1.c=arr;
	arr1.l=(unsigned int)(k);
	return arr1;
}
 void delete_string_array(str_array arr)
 {
	 unsigned int i=0;
	 while (i!=arr.l)
	 {
		 free(arr.c[i]);
		 i++;
	 }
	 free(arr.c);
 }

