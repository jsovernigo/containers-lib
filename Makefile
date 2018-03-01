OS		=$(shell uname)
CC		=gcc
CFLAGS	=-g -Wall -Werror -std=c99 -fPIC

all: buildlibs

test: linkedlist.o hashtable.o
	$(CC) $(CFLAGS) hashtable.o linkedlist.o test.c -o testHash -I.

install: cpheaders buildlibs
cpheaders: hashtable.h linkedlist.h
	cp hashtable.h /usr/include/
	cp linkedlist.h /usr/include/

buildlibs: linkedlist.o hashtable.o
ifeq ($(OS),Darwin)
	$(CC) -dynamiclib -undefined suppress -flat_namespace linkedlist.o hashtable.o -o libcontainers.dylib
else
	$(CC) -shared -Wl,-soname,liblinkedlist.so -o liblinkedlist.so linkedlist.o
	$(CC) -shared -Wl,-soname,libhashtable.so -o libhashtable.so hashtable.o
endif


hashtable.o: hashtable.c hashtable.h
	$(CC) $(CFLAGS) hashtable.c -c -I.

linkedlist.o: linkedlist.c linkedlist.h
	$(CC) $(CFLAGS) linkedlist.c -c -I.

clean:
	rm linkedlist.o vector.o hashtable.o testhash
