#include <stdio.h>
#include <stdlib.h>

#include "../include/dictionary.h"

int main(int argc, char** argv)
{
	dictionary_t* dict = upload_dict("dict_test");
	
	FILE* file = fopen("the_little_prince.txt", "r");
	FILE* encrypt = fopen("encrypted_text.txt", "w+");
	
	if (dict != NULL)
	{
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
	}
	
	fclose(file);
	fclose(encrypt);
	destroy_dict(dict);
	return 0;
}
