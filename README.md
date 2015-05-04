# super_encryptator_4MIN12
Project : Super-Encryptator (C Language)

----------------------------------

/ ! \ BEFORE STARTING: Be sure that you have created a repository named 'dict'. If it is not the case, your programs will not work at all ...

----------------------------------

How to use the Super-Encryptator ?

* Compilation: there is a MakeFile. 
  	- `make key_generator`: program to generate a dictionary file.
	- `make encrypt`: to encrypt a text file. You must have generated a dictionary file before.
	- `make decrypt`: to decrypt a text file. You must have generated a dictionary file before.
	- `make tests`: to compile the tests program.
	- `make`: compilation of all programs.
	
* Generate a dictionary file:
	Use the program key_generator with 2 arguments: the secret key, and a name for the output file.
	E.G.: A file name 'dict1' with the key 'AZERTY':
	- WINDOWS: `./key_generator.exe AZERTY dict1`
	- MAC/UNIX: `./key_generator AZERTY dict1`
	
* Encrypt a text file: 
	Use the program encrypt with 3 arguments: the dictionary file, the original text file to encrypt, the output text file name.
	E.G.: Use 'dict1' to encrypt 'example.txt' into 'enc.txt'
	- WINDOWS: `./encrypt.exe dict1 example.txt enc.txt`
	- MAC/UNIX: `./encrypt dict1 example.txt enc.txt`
		
* Decrypt a text file: 
	Use the program decrypt with 3 arguments: the dictionary file, the encrypted text file to decrypt, the output text file name.
	E.G.: Use 'dict1' to decrypt 'enc.txt' into 'dec.txt'
	- WINDOWS: `./decrypt.exe dict1 enc.txt dec.txt`
	- MAC/UNIX: `./decrypt dict1 enc.txt dec.txt`
		
For further information about the specs and the encrypting method, please have a look on file 'cryptation.pdf'.
