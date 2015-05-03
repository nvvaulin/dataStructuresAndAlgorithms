#include <iostream>
#include <conio.h>
#include <stdlib.h>
using namespace std;
struct str_array
{
	char** c;
	unsigned int l;
};
 void delete_string_array(str_array);

 str_array split(const char *str, const char *delim);