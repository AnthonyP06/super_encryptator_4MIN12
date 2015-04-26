#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/dictionary.h"

int main(int argc, char** argv)
{
	// Are there two arguments ?
	if (argv[1] == NULL || argv[2] == NULL)
	{
		printf("One or two argument(s) missing. Dictionary not created.\n");
		printf("Please re-launch the application.\n");
		return -1;
	}
	
	// Are there more than 2 arguments ?
	if (argv[3] != NULL)
	{
		printf("There are more than 2 arguments. Dictionary not created.\n");
		printf("Please re-launch the application.\n");
		return -1;
	}
	
	// Correct number of arguments
	{
		dictionary_t* dict = init_dict();
		
		// Did the initialization succeed ?
		if (dict == NULL)
		{
			printf("An error occurred. Dictionary not created.\n");
			printf("Please re-launch the application.\n");
			return -1;
		}
		
		// Is the key valid ?
		if (is_valid(argv[1]) == 0)
		{
			printf("The key is not valid. Dictionary not created.\n");
			printf("Please re-launch the application.\n");
			destroy_dict(dict);
			return -1;
		}
		
		// Assign the key
		assign_key(dict, argv[1]);
		
		// Pathname file, max size : 64
		char path[64] = "dict/";
		strncat(path, argv[2], 64);
		
		// Create a new file to save the dictionary.
		FILE* file = fopen(path, "w+");
		
		// Is the file correctly opened/created ?
		if (file == NULL)
		{
			printf("An error occurred. Dictionary not created.\n");
			printf("Please re-launch the application.\n");
			destroy_dict(dict);
			return -1;
		}
		
		fwrite(dict->key, sizeof(char), strlen(dict->key), file);
		fputc('\n', file);
		fwrite(dict->regular_dict, sizeof(char), sizeof(dict->regular_dict), file);
		fputc('\n', file);
		fwrite(dict->encrypted_dict, sizeof(char), sizeof(dict->encrypted_dict), file);
		
		fclose(file);
		
		destroy_dict(dict);
		
		return 0;
	}
}