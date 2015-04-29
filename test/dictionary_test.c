#include <stdio.h>
#include <string.h>

# include "../include/dictionary.h"

/* ------------------------------------------------------- */

// Keep the number of failed tests.
size_t nb_failures = 0;

// Check if the given test has passed or not.
#define CHECK( test_passed )                 \
{                                            \
  if (!((test_passed)))                      \
  {                                          \
    ++nb_failures;                           \
    printf("Failure line %u \n", __LINE__);  \
  }                                          \
}

/* ------------------------------------------------------- */

int main(int argc, char** argv)
{
	// Check that the ASCII is correctly filled in
	{
		dictionary_t* dict = init_dict();
		
		for (int i = 0; i<SIZE_DICT; ++i)
		{
			CHECK(dict->regular_dict[i] == i+32);
		}
		
		destroy_dict(dict);
	}
	
	// Check the validity of different keys
	{
		char* key1 = "JDAcK";
		CHECK(is_valid(key1) == 1);
		char* key2 = "aakcjs";
		CHECK(is_valid(key2) == 0);
		char* key3 = "Kednchk";
		CHECK(is_valid(key3) == 0);
		char* key4 = "";
		CHECK(is_valid(key4) == 0);
		char* key5 = "azertyuiopqsdfghjklmwxcvbn1234";
		CHECK(is_valid(key5) == 0);
		char* key6 = "ujd2";
		CHECK(is_valid(key6) == 0);
	}
	
	// Check the assignment of a key.
	{
		// Impossible to assign a key to a NULL pointer.
		CHECK(assign_key(NULL, "key") == -1);
		
		dictionary_t* dict = init_dict();
		
		if (dict != NULL)
		{
			CHECK(assign_key(dict, "myKey") == 0);
			CHECK(strncmp(dict->key,"myKey",MAX_KEY_SIZE) == 0);
		}
		
		destroy_dict(dict);
	}
	
	// Check the assignment of an encrypted dictionary
	{
		// Impossible to assign an encrypted dictionary to a NULL pointer
		CHECK(assign_encrypted_dict(NULL, " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~") == -1)
		
		dictionary_t* dict = init_dict();
		
		if (dict != NULL)
		{
			// Too short dictionary to be assigned.
			CHECK(assign_encrypted_dict(dict, "DICTIONARY") == -1);
			
			CHECK(assign_encrypted_dict(dict, " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~") == 0);
			CHECK(strncmp(dict->encrypted_dict, " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~", SIZE_DICT) == 0);
		}
		
		destroy_dict(dict);
	}
	
	// Check the file generation
	{
		// Impossible to generate a file from nothing
		CHECK(generate_file(NULL, "dict_test") == -1);
		
		dictionary_t* dict = init_dict();
		
		if (dict != NULL)
		{
			assign_key(dict, "myKey");
			CHECK(generate_file(dict, "") == -1);
			CHECK(generate_file(dict, "dict_test") == 0);
		}
		
		destroy_dict(dict);
	}
	
	// Check the uploading of a file.
	{
		dictionary_t* dict = init_dict();
		
		if (dict != NULL)
		{
			assign_key(dict, "myKey");
			
			// Is the fill well generated ?
			if (generate_file(dict, "dict_test") == -1)
			{
				destroy_dict(dict);
			}
			
			// Test with a dictionary not in the repository
			dictionary_t* dict_up = upload_dict("wrong_dict");
			CHECK(dict_up == NULL);
			
			// Test with an existing dictionary
			dict_up = upload_dict("dict_test");
			if(dict_up != NULL);
			{
				CHECK(strncmp(dict->key, "myKey", MAX_KEY_SIZE) == 0);
				CHECK(strncmp(dict->regular_dict, " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~", SIZE_DICT) == 0);
				CHECK(strncmp(dict->encrypted_dict, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", SIZE_DICT) == 0);
			}
		}
		
		destroy_dict(dict);
	}
	
	// Number of failures.
  printf("%lu failure(s)\n", nb_failures);
	
	return 0;
}
