CC		=gcc
CFLAGS	=-g -Wall -Werror -std=c99

all: linkedlist.o hashtable.o

test: linkedlist.o hashtable.o
	$(CC) $(CFLAGS) hashtable.o linkedlist.o test.c -o testHash -I./linkedlist -I./hashtable

hashtable.o: hashtable/hashtable.c hashtable/hashtable.h
	$(CC) $(CFLAGS) hashtable/hashtable.c -c -I./hashtable -I./linkedlist

linkedlist.o: linkedlist/linkedlist.c linkedlist/linkedlist.h
	$(CC) $(CFLAGS) linkedlist/linkedlist.c -c -I./linkedlist
