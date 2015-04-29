#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/dictionary.h"

#define MAX_SIZE 128 // Maximum size for a dictionary name

/* ---------------------------------------------------------------*/

// Create a new dictionary. 
// The regular dictionary is filled in with ASCII chars from 32 to 126.
// The encrypted dictionary is initialized with the ASCII order.
dictionary_t* init_dict()
{
	dictionary_t* dict = malloc(sizeof(dictionary_t));
	
	// Did the allocation succeed ?
	if (dict == NULL)
	{
		return NULL;
	}
	
	char* key	= malloc(MAX_KEY_SIZE*sizeof(char));
	
	// Did the allocation succeed ?
	if (key == NULL)
	{
		free(dict);
		return NULL;
	}
	
	// Everything is OK
	
	// We do not have the key yet.
	dict->key = key;
	
	// Fill in the ASCII dictionary
	for (unsigned int i = 0; i<SIZE_DICT; ++i)
	{
		dict->regular_dict[i] = 32+i;
		dict->encrypted_dict[i] = 32+i; 
	}
	
	return dict;
}

/* ---------------------------------------------------------------*/

// Erase a dictionary
void destroy_dict(dictionary_t* dict)
{
	if (dict != NULL)
	{
		dict->key = NULL;
		free(dict->key);
		dict = NULL;
		free(dict);
	}
}

/* ---------------------------------------------------------------*/

// Check the validity of a key. Returns 1 if the key is valid, 0 otherwise.
int is_valid(const char* key)
{
	// Is the key longer than the alphabet ?
	if (strlen(key) > MAX_KEY_SIZE)
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

/* ---------------------------------------------------------------*/

// Capitalize the key
void capitalize_key(char* key)
{
	for(int i = 0; i < strlen(key); ++i)
	{
		if(*(key+i)>90)
		{
			*(key+i)-=32;
		}
	}
}

/* ---------------------------------------------------------------*/

// Encrypt the dictionary. Returns 0 if everything is OK, -1 otherwise.
int encrypted_dict(dictionary_t* dict, char* key)
{
	if(is_valid(key) == -1)
	{
		return -1;
	}
	
	if (dict == NULL)
	{
		return -1;
	}

	// Capitalize the key (does not change the result)
	capitalize_key(key);
	
	// Fill the encrypted dictionary with the key
	for(int i = 0; i < strlen(key); ++i)
	{
		dict->encrypted_dict[i+33] = *(key+i);
		dict->encrypted_dict[i+65] = dict->encrypted_dict[i+33]+32;
	}

	//Fill the last cases of the encrypted dictionary
	int compteur = 0;							// Boolean
	int compteurClef = 0;						// Number of letter of the key already read
	for(int i = 65; i <= 90; ++i)					// Loop on the alphabet
	{
		for(int j = 0; j < strlen(key); ++j)	// Loop on the key
		{
			if(dict->regular_dict[i-32] == *(key+j))		// If the letter is in the key
			{
				compteur++;
			}
		}
		if(compteur == 0)
		{
			dict->encrypted_dict[i+strlen(key)-32-compteurClef] = i;			// Fill the capitalized letter
			dict->encrypted_dict[i+strlen(key)-32-compteurClef+32] = i+32;	// Fill the lower case letter
			compteur = 0;
		}
		else
		{
			compteur = 0;
			compteurClef++;
		}
	}
	return 0;
}

/* ---------------------------------------------------------------*/

// Assign a key to a dictionary. Returns 0 if everything is OK, -1 otherwise.
int assign_key(dictionary_t* dict, const char* key)
{
	// It's an error to assign a key to an empty dictionary
	if (dict == NULL)
	{
		return -1;
	}
	else
	{
		strncpy(dict->key, key, MAX_KEY_SIZE);
		return 0;
	}
}

/* ---------------------------------------------------------------*/

// Assign an encrypted dictionary to a dictionary object. Returns 0 if everything is OK, -1 otherwise.
int assign_encrypted_dict(dictionary_t* dict, const char* encrypted_dict)
{
	// The encrypted dictionary given as a parameter must be 95-chars length.
	if (strlen(encrypted_dict) != SIZE_DICT)
	{
		return -1;
	}
	
	// It's an error to assign something to an empty dictionary
	if (dict == NULL)
	{
		return -1;
	}
	else
	{
		strncpy(dict->encrypted_dict, encrypted_dict, SIZE_DICT);
		return 0;
	}
}

/* ---------------------------------------------------------------*/

// Returns the index of the encrypted dictionary where the char 'c' (given as a parameter) in located.
// Returns -1 if the char 'c' is not in the dictionary.
int index(const char c, const dictionary_t* dict)
{
	int position = -1;
	for (unsigned int i=0; i<SIZE_DICT; ++i)
	{
		if (dict->encrypted_dict[i] == c)
		{
			position = i;
		}
	}
	return position;
}

/* ---------------------------------------------------------------*/

// Generate a file with the dictionary, with the given name "dst".
// Returns 0 if everything is OK, -1 otherwise.
int generate_dict_file(dictionary_t* dict, const char* dst)
{
	// Non-existing dictionary.
	if (dict == NULL)
	{
		return -1;
	}
	
	// Path where the dictionary file will be created
	char path[MAX_SIZE] = "dict/";
	strncat(path, dst, MAX_SIZE);
	
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
	fwrite(dict->regular_dict, sizeof(char), SIZE_DICT, file);
	fputc('\n', file);
	fwrite(dict->encrypted_dict, sizeof(char), SIZE_DICT, file);
	
	fclose(file);
	
	return 0;
}

/* ---------------------------------------------------------------*/

// Create a dictionary object from a dictionary file named "src".
// Returns the dictionary is everything is OK, a NULL pointer otherwise.
dictionary_t* upload_dict(const char* src)
{
	// Path where the dictionary is stored
	char path[MAX_SIZE] = "dict/";
	strncat(path, src, MAX_SIZE);
	
	FILE* file = fopen(path, "r");
	
	// Is the file correctly opened ?
	if (file == NULL)
	{
		return NULL;
	}
	
	dictionary_t* dict = init_dict();
	
	// Is the dictionary correctly created ?
	if (dict == NULL)
	{
		fclose(file);
		return NULL;
	}
	
	char line[MAX_SIZE] = "";
	fgets(line, MAX_SIZE, file); // Dictionary's key.
	line[strlen(line)-1] = '\0'; // Delete the '\n' at the end of the line.
	
	// Is the key well assigned ?
	if(assign_key(dict, line) == -1)
	{
		fclose(file);
		return NULL;
	}
	
	fgets(line, MAX_SIZE, file); // ASCII dictionary, already filled in thanks to the init_dict() function.
	fgets(line, MAX_SIZE, file); // Encrypted dictionary
	
	// Is the encrypted dictionary well assigned ?
	if(assign_encrypted_dict(dict, line) == -1)
	{
		fclose(file);
		return NULL;
	}
	
	// Everything is OK
	fclose(file);
	return dict;
}

/* ---------------------------------------------------------------*/

// Write in a file 'dst_file' from a file 'src_file' using a dictionary 'dict'.
// If you want to encrypt a file, you must use the mode 'e'.
// If you want to decrypt a file, you must use the mode 'd'.
// Returns 0 if everything is OK, -1 otherwise.
int write_in_file(FILE* src_file, FILE* dst_file, const dictionary_t* dict, const char mode)
{
	// Mode not supported
	if (mode != 'e' && mode != 'd')
	{
		printf("This mode is not supported. You must use 'e' (encrypt) or 'd' (decrypt).\n");
		return -1;
	}
	
	if (src_file == NULL)
	{
		return -1;
	}
	
	if (dst_file == NULL)
	{
		return -1;
	}
	
	if (dict == NULL)
	{
		return -1;
	}
	
	// Mode 'e'
	if (mode == 'e')
	{
		char c = ' ';
		while (c != EOF)	// EOF : End Of File char
		{
			c = fgetc(src_file);
			if (c == '\n')
			{
				fputc(c, dst_file);
			}
			else
			{
				fputc(dict->encrypted_dict[c-32], dst_file);
			}
		}
		return 0;
	}
	
	return 0;
}

/* ---------------------------------------------------------------*/

// Prints both regular and encrypted dictionaries
void print(const dictionary_t* dict)
{
	if (dict != NULL)
	{
		printf("Key : %s\n", dict->key);
		for (unsigned int i=0; i<SIZE_DICT; ++i)
		{
			printf("%c <-> %c\n", dict->regular_dict[i], dict->encrypted_dict[i]);
		}
	}
}
