CC = gcc
CFLAGS = -std=c99 -Wall -Werror -g -O0

all: dict

dict: key_generator.o
	$(CC) $(CFLAGS) $^ -o $@ 
	
key_generator.o: src/key_generator.c
	$(CC) $(CFLAGS) -c $^ include/dictionary.h
	
clean: 
	rm -rf *.a *.o include/*.h.gch

distclean: clean
	rm -rf dict.exe