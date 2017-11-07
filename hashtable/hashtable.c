#include "hashtable.h"
#include "linkedlist.h"

#include <stdlib.h>
#include <stddef.h>
#include <inttypes.h>

struct __key_pair
{
	uint8_t* key;
	void* obj;
};

struct hashtable
{
	size_t size;
	struct linkedlist ** table;

	uint64_t (*hash)(uint8_t* key);
};

struct __key_pair* __create_key_pair(uint8_t* key, void* obj)
{
	struct __key_pair* new_pair;

	/* the key is somehow invalid. */
	if (key == NULL || key[0] == '\0')
	{
		return NULL;
	}
	else if (obj == NULL)
	{
		return NULL;
	}

	/* create the new pair */
	new_pair = malloc(sizeof(__key_pair));
	if (new_pair == NULL)
	{
		return NULL;
	}

	new_pair->key = key;
	new_pair->obj = obj;

	return new_pair;
}

struct hashtable* create_hashtable(size_t size, uint64_t (*hash)(uint8_t* key))
{
	struct hashtable* table;

	if (size <= 0)
	{
		return NULL;
	}
	else if (hash == NULL)
	{
		hash = &djb2_hash;
	}

	table = malloc(sizeof(table));
	if (table == NULL)
	{
		return NULL;
	}

	table->size = size;
	table->table = malloc(sizeof(linked_list) * table->size);

	/* set all table entries to NULL before use.  NULL specifies an empty bucket. */
	bzero(table->table, table->size);

	table->hash = hash;

	return table;
}

int __key_pair_equals(void* key1, void* key2)
{
	struct __key_pair* first;
	struct __key_pair* second;

	first = (struct __key_pair*) key1;
	second = (struct __key_pair*) key2;

	return strcmp(first->key, second->key);
}

uint64_t djb2_hash(uint8_t* key)
{
	uint8_t c;
	uint64_t digest;

	digest = 5381;

	while(c = *key ++)
	{
		digest = ((digest << 5) + digest) + c;
	}

	return digest;
}

int put_entry(struct table* table, uint8_t key, void* data)
{
	uint64_t index;
	struct __key_pair* entry;

	if (table == NULL)
	{
		return -1;
	}
	else if (data == NULL)
	{
		return -2;
	}
	
	entry = __create_key_pair(key, data);

	index = table->hash(key) % table->size;

	if (table->table[index] == NULL)
	{
		table->table[index] = createlinkedlist();
	}

	append(table->table[index], entry);

	return 0;
}

void* get_entry(struct table* table, uint8_t* key)
{
	uint64_t index;
	void* entry;

	if (table == NULL)
	{
		return -1;
	}
	else if (data == NULL)
	{
		return -2;
	}

	index = table->hash(key) % table->size;

	if (table->table[index] == NULL)
	{
		return NULL;
	}

	/* TODO create linkedlist function called get, takes list and equals */
	entry = get(table->table[index], __equals_key_pair);

	return entry;
}
