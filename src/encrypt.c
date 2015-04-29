#include <stdio.h>
#include <stdlib.h>

#include "../include/dictionary.h"

int main(int argc, char** argv)
{
	dictionary_t* dict = upload_dict("dict_test");
	
	if (dict == NULL)
	{
		printf("Impossible to upload the dictionary dict_test. Please check the file name.\n");
		printf("Please re-launch the application.\n");
		return -1;
	}
	
	print(dict);
	
	FILE* file = fopen("the_little_prince.txt", "r");
	FILE* encrypt = fopen("encrypted_text.txt", "w+");
	
	char c = ' ';
	while (c != EOF)
	{
		c = fgetc(file);
		if (c == '\n')
		{
			fputc(c, encrypt);
		}
		else
		{
			fputc(dict->encrypted_dict[c-32], encrypt);
		}
	}
	
	fclose(file);
	fclose(encrypt);
	destroy_dict(dict);
	return 0;
}
