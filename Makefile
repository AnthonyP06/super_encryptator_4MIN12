CC = gcc
CFLAGS = -std=c99 -Wall -Werror -g -O0

all: key_generator

key_generator: key_generator.o
	$(CC) $(CFLAGS) $^ -o $@ 
	
key_generator.o: src/key_generator.c
	$(CC) $(CFLAGS) -c $^
	
clean: 
	rm -rf *.a *.o

distclean: clean
	rm -rf key_generator.exe