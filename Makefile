CC = gcc
CFLAGS = -std=c99 -Wall -Werror -g -O0

all: key_generator encrypt decrypt tests

key_generator: dictionary.o key_generator.o
	$(CC) $(CFLAGS) $^ -o $@

key_generator.o: src/key_generator.c
	$(CC) $(CFLAGS) -c $^

encrypt: dictionary.o encrypt.o
	$(CC) $(CFLAGS) $^ -o $@
	
encrypt.o: src/encrypt.c
	$(CC) $(CFLAGS) -c $^

decrypt: dictionary.o decrypt.o
	$(CC) $(CFLAGS) $^ -o $@
	
decrypt.o: src/decrypt.c
	$(CC) $(CFLAGS) -c $^
	
tests: dictionary.o dictionary_test.o
	$(CC) $(CFLAGS) $^ -o $@ 
	
dictionary_test.o: test/dictionary_test.c
	$(CC) $(CFLAGS) -c $^
	
dictionary.o: src/dictionary.c
	$(CC) $(CFLAGS) -c $^

clean: 
	rm -rf *.a *.o

distclean: clean
	rm -rf *.exe dict/* *.txt
	rm -rf key_generator encrypt tests
	