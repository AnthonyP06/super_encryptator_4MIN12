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
			CHECK(assign_key(dict, "AZERTY") == 0);
			CHECK(strncmp(dict->key,"AZERTY",MAX_KEY_SIZE) == 0);
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
	
	// Check function encrypt_dict()
	{
		dictionary_t* dict = init_dict();
		
		if (dict != NULL)
		{			
			// Error cases
			CHECK(encrypt_dict(NULL, "AZERTY") == -1);
			CHECK(encrypt_dict(dict, "HELLOWORLD") == -1);
			
			CHECK(encrypt_dict(dict, "AZERTY") == 0);
			
			// Verification of each characters (letters)
			CHECK(dict->encrypted_dict[33] == 'A');
			CHECK(dict->encrypted_dict[34] == 'Z');
			CHECK(dict->encrypted_dict[35] == 'E');
			CHECK(dict->encrypted_dict[36] == 'R');
			CHECK(dict->encrypted_dict[37] == 'T');
			CHECK(dict->encrypted_dict[38] == 'Y');
			CHECK(dict->encrypted_dict[39] == 'B');
			CHECK(dict->encrypted_dict[40] == 'C');
			CHECK(dict->encrypted_dict[41] == 'D');
			CHECK(dict->encrypted_dict[42] == 'F');
			CHECK(dict->encrypted_dict[43] == 'G');
			CHECK(dict->encrypted_dict[44] == 'H');
			CHECK(dict->encrypted_dict[45] == 'I');
			CHECK(dict->encrypted_dict[46] == 'J');
			CHECK(dict->encrypted_dict[47] == 'K');
			CHECK(dict->encrypted_dict[48] == 'L');
			CHECK(dict->encrypted_dict[49] == 'M');
			CHECK(dict->encrypted_dict[50] == 'N');
			CHECK(dict->encrypted_dict[51] == 'O');
			CHECK(dict->encrypted_dict[52] == 'P');
			CHECK(dict->encrypted_dict[53] == 'Q');
			CHECK(dict->encrypted_dict[54] == 'S');
			CHECK(dict->encrypted_dict[55] == 'U');
			CHECK(dict->encrypted_dict[56] == 'V');
			CHECK(dict->encrypted_dict[57] == 'W');
			CHECK(dict->encrypted_dict[58] == 'X');
			
			CHECK(dict->encrypted_dict[65] == 'a');
			CHECK(dict->encrypted_dict[66] == 'z');
			CHECK(dict->encrypted_dict[67] == 'e');
			CHECK(dict->encrypted_dict[68] == 'r');
			CHECK(dict->encrypted_dict[69] == 't');
			CHECK(dict->encrypted_dict[70] == 'y');
			CHECK(dict->encrypted_dict[71] == 'b');
			CHECK(dict->encrypted_dict[72] == 'c');
			CHECK(dict->encrypted_dict[73] == 'd');
			CHECK(dict->encrypted_dict[74] == 'f');
			CHECK(dict->encrypted_dict[75] == 'g');
			CHECK(dict->encrypted_dict[76] == 'h');
			CHECK(dict->encrypted_dict[77] == 'i');
			CHECK(dict->encrypted_dict[78] == 'j');
			CHECK(dict->encrypted_dict[79] == 'k');
			CHECK(dict->encrypted_dict[80] == 'l');
			CHECK(dict->encrypted_dict[81] == 'm');
			CHECK(dict->encrypted_dict[82] == 'n');
			CHECK(dict->encrypted_dict[83] == 'o');
			CHECK(dict->encrypted_dict[84] == 'p');
			CHECK(dict->encrypted_dict[85] == 'q');
			CHECK(dict->encrypted_dict[86] == 's');
			CHECK(dict->encrypted_dict[87] == 'u');
			CHECK(dict->encrypted_dict[88] == 'v');
			CHECK(dict->encrypted_dict[89] == 'w');
			CHECK(dict->encrypted_dict[90] == 'x');
		}
		
		destroy_dict(dict);
	}
	
	// Check the file generation
	{
		// Impossible to generate a file from nothing
		CHECK(generate_dict_file(NULL, "dict_test") == -1);
		
		dictionary_t* dict = init_dict();
		
		if (dict != NULL)
		{
			assign_key(dict, "AZERTY");
			CHECK(generate_dict_file(dict, "") == -1);
			CHECK(generate_dict_file(dict, "dict_test") == 0);
		}
		
		destroy_dict(dict);
	}
	
	// Check the uploading of a file.
	{
		dictionary_t* dict = init_dict();
		
		if (dict != NULL)
		{
			assign_key(dict, "AZERTY");
			
			// Is the fill well generated ?
			if (generate_dict_file(dict, "dict_test") == -1)
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
				CHECK(strncmp(dict->key, "AZERTY", MAX_KEY_SIZE) == 0);
				CHECK(strncmp(dict->regular_dict, " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~", SIZE_DICT) == 0);
				CHECK(strncmp(dict->encrypted_dict, " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~", SIZE_DICT) == 0);
			}
		}
		
		destroy_dict(dict);
	}
	
	// Check function index()
	{
		dictionary_t* dict = init_dict();
		
		if (dict != NULL)
		{
			assign_key(dict, "AZERTY");
			
			// After the initialization of a dictionary, characters are in the right order.
			for (unsigned int i=0; i<SIZE_DICT; ++i)
			{
				CHECK(index(*(dict->regular_dict+i), dict) == i);
			}
			
			encrypt_dict(dict, dict->key);
			
			// Tests for the first characters.
			CHECK(index('A', dict) == 33);
			CHECK(index('Z', dict) == 34);
			CHECK(index('E', dict) == 35);
			CHECK(index('R', dict) == 36);
			CHECK(index('T', dict) == 37);
			CHECK(index('Y', dict) == 38);
			CHECK(index('B', dict) == 39);
			CHECK(index('C', dict) == 40);
			CHECK(index('D', dict) == 41);
		}
		
		destroy_dict(dict);
	}
	
	// Number of failures.
  printf("%lu failure(s)\n", nb_failures);
	
	return 0;
}
