#include <stdio.h>
#include <stdlib.h>

#include "../include/dictionary.h"

int main(int argc, char** argv)
{
	// Are there three arguments ?
	if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL)
	{
		printf("One, two or three argument(s) missing. Impossible to encrypt anything.\n");
		printf("Please re-launch the application.\n");
		return -1;
	}
	
	// Are there more than 3 arguments ?
	if (argv[4] != NULL)
	{
		printf("There are more than 3 arguments. Text file not encrypted.\n");
		printf("Please re-launch the application.\n");
		return -1;
	}
	
	// Correct number of arguments
	{
		dictionary_t* dict = upload_dict(argv[1]);
		
		if (dict == NULL)
		{
			printf("Impossible to upload the dictionary dict_test. Please check the file name.\n");
			printf("Please re-launch the application.\n");
			return -1;
		}
		
		FILE* file = fopen(argv[2], "r");
		FILE* encrypt = fopen(argv[3], "w+");
		
		// Is the original text file correctly opened ?
		if (file == NULL)
		{
			printf("An error occurred. Please check the file name of the file you want to encrypt.\n");
			printf("Please re-launch the application.\n");
			fclose(encrypt);
			destroy_dict(dict);
			return -1;
		}
		
		// Is the encrypted text file correctly generated ?
		if (encrypt == NULL)
		{
			printf("An error occurred.\n");
			printf("Please re-launch the application.\n");
			fclose(file);
			destroy_dict(dict);
			return -1;
		}
		
		// Everything is OK
		
		// Write in the encrypted text file
		if (write_in_file(file, encrypt, dict, 'e') == -1)
		{
			printf("An error occurred while writing in the encrypted text file.\n");
			printf("Please re-launch the application.\n");
			fclose(file);
			fclose(encrypt);
			destroy_dict(dict);
			return -1;
		}
		
		fclose(file);
		fclose(encrypt);
		destroy_dict(dict);
		return 0;
	}
	
}
