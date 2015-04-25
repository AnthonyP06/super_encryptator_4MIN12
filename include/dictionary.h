#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

// A dictionary
struct dictionary
{
	// The key of the dictionary
	char* key;
	
	// The ASCII dictionary, 95 : 126-32+1 char to encode
	char regular_dict[95]; 
	
	// The encrypted dictionary
	char encrypted_dict[95];
};

typedef struct dictionary dictionary_t;

// Create an new dictionary
dictionary_t* init_dict();

// Erase a dictionary
void destroy_dict(dictionary_t* dict);

#endif //_DICTIONARY_H_