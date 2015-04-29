#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#define SIZE_DICT 95 // 95 : 126-32+1 chars to encode
#define MAX_KEY_SIZE 26 // Impossible to have more encoding chars than the size of alphabet

// A dictionary
struct dictionary
{
	// The key of the dictionary
	char* key;
	
	// The ASCII dictionary
	char regular_dict[SIZE_DICT]; 
	
	// The encrypted dictionary
	char encrypted_dict[SIZE_DICT];
};

typedef struct dictionary dictionary_t;

/* ----------------------------------------------------------- */

// Create an new dictionary
// The regular dictionary is filled in with ASCII chars from 32 to 126.
// The encrypted dictionary is initialized with the ASCII order.
dictionary_t* init_dict();

// Erase a dictionary
void destroy_dict(dictionary_t* dict);

// Check the validity of a key. Returns 1 if the key is valid, 0 otherwise.
int is_valid(const char* key);

// Encrypt the dictionary. Returns 0 if everything is OK, -1 otherwise.
int encrypt_dict(dictionary_t* dict, char* key);

// Capitalize the key
void capitalize_key(char* key);

// Assign a key to a dictionary. Returns 0 if everything is OK, -1 otherwise.
int assign_key(dictionary_t* dict, const char* key);

// Assign an encrypted dictionary to a dictionary object. Returns 0 if everything is OK, -1 otherwise.
int assign_encrypted_dict(dictionary_t* dict, const char* encrypted_dict);

// Returns the index of the encrypted dictionary where the char 'c' (given as a parameter) in located.
// Returns -1 if the char 'c' is not in the dictionary.
int index(const char c, const dictionary_t* dict);

// Generate a file with the dictionary, with the given name "dst".
// Returns 0 if everything is OK, -1 otherwise.
int generate_dict_file(dictionary_t* dict, const char* dst);

// Create a dictionary object from a dictionary file named "src".
// Returns the dictionary is everything is OK, a NULL pointer otherwise.
dictionary_t* upload_dict(const char* src);

// Write in a file 'dst_file' from a file 'src_file' using a dictionary 'dict'.
// If you want to encrypt a file, you must use the mode 'e'.
// If you want to decrypt a file, you must use the mode 'd'.
// Returns 0 if everything is OK, -1 otherwise.
int write_in_file(FILE* src_file, FILE* dst_file, const dictionary_t* dict, const char mode);

// Prints both regular and encrypted dictionaries
void print(const dictionary_t* dict);

#endif //_DICTIONARY_H_
