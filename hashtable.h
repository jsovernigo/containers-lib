#ifndef __GSOVERNIGO_HASHTABLE_H__
#define __GSOVERNIGO_HASHTABLE_H__

struct hashtable;

struct hashtable* create_hashtable(size_t size, uint64_t (*hash)(uint8_t* key));

uint64_t djb2_hash(uint8_t* key);

int put_entry(struct table* table, uint8_t key, void* data);

void* get_entry(struct table* table, uint8_t* key);

#endif
