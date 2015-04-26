#include <stdio.h>
#include <stdlib.h>

#include "../include/dictionary.h"

int main(const int argc, const char** argv)
{
	dictionary_t* dict = init_dict();
	
	print(dict);
	
	destroy_dict(dict);
	
	return 0;
}