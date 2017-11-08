#ifndef __JSOVERNIGO_LINKEDLIST_H__
#define __JSOVERNIGO_LINKEDLIST_H__

#include <stdlib.h>

struct linkedlist;

/**
 *
 */
struct linkedlist* makeList();

/**
 *
 */
void destroyList(struct linkedlist* list, void (*destroy)(void*));


int push(struct linkedlist* list, void* data);

int append(struct linkedlist* list, void* data);

int insert(struct linkedlist* list, void* data, int (*compare)(void*, void*), int index);

int remove(struct linkedlist* list, void* data);

void* get(struct linkedlist* list, int index);

size_t getLength(struct linkedlist* list);

#endif

