#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/dictionary.h"

// Create a new dictionary. 
// The regular dictionary is filled in with ASCII chars from 32 to 126.
// The encrypted dictionary is initialized with a unique char : 'A'.
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
		dict->encrypted_dict[i] = 65; //'A'
	}
	
	return dict;
}

// Erase a dictionary
void destroy_dict(dictionary_t* dict)
{
	if (dict != NULL)
	{
		dict->key = NULL;
		free(dict);
	}
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

// Assign a key to a dictionary. Returns 0 if everything is OK, -1 otherwise.
int assign_key(dictionary_t* dict, char* key)
{
	// It's an error to assign a key to an empty dictionary
	if (dict == NULL)
	{
		return -1;
	}
	else
	{
		dict->key = key;
		return 0;
	}
}

// Generate a file with the dictionary, with the given name "dst".
// Returns 0 if everything is OK, -1 otherwise.
int generate_file(dictionary_t* dict, char* dst)
{
	// Non-existing dictionary.
	if (dict == NULL)
	{
		return -1;
	}
	
	// Pathname, max size : 64
	char path[64] = "dict/";
	strncat(path, dst, 64);
	
	// Create a new file to save the dictionary.
	FILE* file = fopen(path, "w+");
	
	// Is the file correctly opened/created ?
	if (file == NULL)
	{
		return -1;
	}
	
	// Everything is OK.
	fwrite(dict->key, sizeof(char), strlen(dict->key), file);
	fputc('\n', file);
	fwrite(dict->regular_dict, sizeof(char), sizeof(dict->regular_dict), file);
	fputc('\n', file);
	fwrite(dict->encrypted_dict, sizeof(char), sizeof(dict->encrypted_dict), file);
	
	fclose(file);
	
	return 0;
}

// Prints both regular and encrypted dictionaries
void print(dictionary_t* dict)
{
	if (dict != NULL)
	{
		for (unsigned int i=0; i<sizeof(dict->regular_dict); ++i)
		{
			printf("%c <-> %c\n", dict->regular_dict[i], dict->encrypted_dict[i]);
		}
	}
}
