#ifndef __JSOVERNIGO_LINKEDLIST_H__
#define __JSOVERNIGO_LINKEDLIST_H__

#include <stdlib.h>

struct linkedlist;

/**
 *
 */
struct linkedlist* make_list();

/**
 *
 */
void destroy_list(struct linkedlist* list, void (*destroy)(void*));


int push(struct linkedlist* list, void* data);

int append(struct linkedlist* list, void* data);

int insert(struct linkedlist* list, void* data, int (*compare)(void*, void*), int index);

void* remove_front(struct linkedlist* list);

int remove_entry(struct linkedlist* list, void* data);

void* get(struct linkedlist* list, int index);

size_t get_length(struct linkedlist* list);

#endif

