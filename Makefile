CC		=gcc
CFLAGS	=-g -Wall -Werror -std=c99 -fPIC

all: buildlibs cpheaders

test: linkedlist.o hashtable.o
	$(CC) $(CFLAGS) hashtable.o linkedlist.o test.c -o testHash -I./linkedlist -I./hashtable

cpheaders: hashtable/hashtable.h linkedlist/linkedlist.h
	cp hashtable/hashtable.h /usr/include/
	cp linkedlist/linkedlist.h /usr/include/

buildlibs: linkedlist.o hashtable.o
	$(CC) -shared -Wl,-soname,liblinkedlist.so -o liblinkedlist.so linkedlist.o
	$(CC) -shared -Wl,-soname,libhashtable.so -o libhashtable.so hashtable.o

hashtable.o: hashtable/hashtable.c hashtable/hashtable.h
	$(CC) $(CFLAGS) hashtable/hashtable.c -c -I./hashtable -I./linkedlist

linkedlist.o: linkedlist/linkedlist.c linkedlist/linkedlist.h
	$(CC) $(CFLAGS) linkedlist/linkedlist.c -c -I./linkedlist
