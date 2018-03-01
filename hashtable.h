#ifndef __GSOVERNIGO_HASHTABLE_H__
#define __GSOVERNIGO_HASHTABLE_H__

#include <stdlib.h>
#include <inttypes.h>

struct hashtable;

struct hashtable* hashtable_make(size_t size, uint64_t (*hash)(char* key));

void hashtable_destroy(struct hashtable* table, void (*destroy)(void*));

uint64_t djb2_hash(char* key);

void* hashtable_put(struct hashtable* table, char* key, void* data);

void* hashtable_get(struct hashtable* table, char* key);

void* hashtable_remove(struct hashtable* table, char* key);

char** hashtable_keys(struct hashtable* table);

#endif
