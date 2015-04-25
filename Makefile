CC = gcc
CFLAGS = -std=c99 -Wall -Werror -g -O0

all: dictionary_test

dictionary_test: dictionary.o dictionary_test.o
	$(CC) $(CFLAGS) $^ -o $@ 
	
dictionary.o: src/dictionary.c
	$(CC) $(CFLAGS) -c $^

dictionary_test.o: test/dictionary_test.c
	$(CC) $(CFLAGS) -c $^
	
clean: 
	rm -rf *.a *.o

distclean: clean
	rm -rf dictionary_test.exe