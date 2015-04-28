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

	

	// Fill in the ASCII dictionary for both regular and encrypted dictionaries

	for (int i = 0; i<sizeof(dict->regular_dict); ++i)

	{

		dict->regular_dict[i] = 32+i;
		dict->encrypted_dict[i] = 32+i;

	}



	// Imagine we have a key

	dict->key = "CBOZD";
	

	// Fill the encrypted dictionary with the key

	for(int i = 0; i < strlen(dict->key); i++)

	{

		dict->encrypted_dict[i+33] = *(dict->key+i);
		dict->encrypted_dict[i+65] = dict->encrypted_dict[i+33]+32;

	}

	//Fill the last cases of the encryted dictionary
	int compteur = 0;							// Boolean
	int compteurClef = 0;						// Number of letter of the key already read
	int i = 0;
	int j = 0;
	for(i = 65; i <= 90; i++)					// Loop on the alphabet
	{
		for(j = 0; j < strlen(dict->key); j++)	// Loop on the key
		{
			if(dict->regular_dict[i-32] == *(dict->key+j))		// If the letter is in the key
			{
				compteur++;
			}
		}
		if(compteur == 0)
		{
			dict->encrypted_dict[i+strlen(dict->key)-32-compteurClef] = i;			// Fill the capitalized letter
			dict->encrypted_dict[i+strlen(dict->key)-32-compteurClef+32] = i+32;	// Fill the lower case letter
			compteur = 0;
		}
		else
		{
			compteur = 0;
			compteurClef++;
		}
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
		printf("Char %d : %c - %c\n", i, dict->regular_dict[i], dict->encrypted_dict[i]);

	}

	

	destroy_dict(dict);

}
