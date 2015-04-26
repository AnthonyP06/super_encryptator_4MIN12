#include <stdio.h>

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
		
		for (int i = 0; i<sizeof(dict->regular_dict); ++i)
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
	
	// Number of failures.
  printf("%lu failure(s)\n", nb_failures);
	
	return 0;
}