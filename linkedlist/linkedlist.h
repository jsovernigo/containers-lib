#ifndef __JSOVERNIGO_LINKEDLIST_H__
#define __JSOVERNIGO_LINKEDLIST_H__

struct linkedlist;

/**
 *
 */
struct linkedlist* makeList();

/**
 *
 */
void destroyList(struct linkedlist* list, void (*destroy)(void*));

#endif

