#include <stdio.h>
#include <stdlib.h>

#include "../include/dictionary.h"

// Create a new dictionary
dictionary_t* init_dict()
{
	dictionary_t* dict = malloc(sizeof(dictionary_t));
	
	// Did the allocation succeed ?
	if (dict == NULL)
	{
		return NULL;
	}
	
	// Everything is OK
	
	// We do not have the key yet
	dict->key = NULL;
	
	// Fill in the ASCII dictionary
	for (int i = 0; i<sizeof(dict->regular_dict); ++i)
	{
		dict->regular_dict[i] = 32+i;
	}
	
	return dict;
}

// Erase a dictionary
void destroy_dict(dictionary_t* dict)
{
	dict->key = NULL;
	free(dict);
}

int main(int argc, char** argv)
{
	dictionary_t* dict = init_dict();
	
	for (int i = 0; i<sizeof(dict->regular_dict); ++i)
	{
		printf("Char %d : %c\n", i, dict->regular_dict[i]);
	}
	
	destroy_dict(dict);
}
