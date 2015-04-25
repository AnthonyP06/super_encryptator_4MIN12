#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Check the validity of a key. Returns 1 if the key is valid, 0 otherwise.
int is_valid(char* key)
{
	// Is the key longer than the alphabet ?
	if (strlen(key) > 26)
	{
		return 0;
	}
	
	// Is the key empty ?
	if (strlen(key) < 1)
	{
		return 0;
	}
	
	// Is there any non-unique or forbidden char ?
	for (unsigned int i = 0; i<strlen(key); ++i)
	{
		// Is it a forbidden char ?
		if ( (key[i] < 65 || key[i] > 90) && (key[i] < 97 || key[i] > 122) )
		{
			return 0;
		}
		
		// Is it a non-unique char ?
		for (unsigned int j=i+1; j<strlen(key); ++j)
		{
			if (key[i] == key[j] || key[i] == key[j]+32 || key[i] == key[j]-32)
			{
				return 0;
			}
		}
	}
	
	// Everything is OK
	return 1;
}

int main(int argc, char** argv)
{
	dictionary_t* dict = init_dict();
	
	for (int i = 0; i<sizeof(dict->regular_dict); ++i)
	{
		printf("Char %d : %c\n", i, dict->regular_dict[i]);
	}
	
	char* key1 = "JDAcK";
	printf("Is %s valid ? %d\n", key1, is_valid(key1));
	char* key2 = "aakcjs";
	printf("Is %s valid ? %d\n", key2, is_valid(key2));
	char* key3 = "Kednchkl";
	printf("Is %s valid ? %d\n", key3, is_valid(key3));
	char* key4 = "";
	printf("Is %s valid ? %d\n", key4, is_valid(key4));
	char* key5 = "azertyuiopqsdfghjklmwxcvbn1234";
	printf("Is %s valid ? %d\n", key5, is_valid(key5));
	
	destroy_dict(dict);
}
