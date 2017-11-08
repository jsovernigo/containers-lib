#include "hashtable.h"
#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <inttypes.h>

struct __key_pair
{
	char* key;
	void* obj;
};

struct hashtable
{
	size_t size;
	struct linkedlist ** table;

	uint64_t (*hash)(char* key);
};

struct __key_pair* __create_key_pair(char* key, void* obj)
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
	new_pair = malloc(sizeof(struct __key_pair));
	if (new_pair == NULL)
	{
		return NULL;
	}

	new_pair->key = key;
	new_pair->obj = obj;

	return new_pair;
}

struct hashtable* create_hashtable(size_t size, uint64_t (*hash)(char* key))
{
	int i;
	struct hashtable* table;


	if (size <= 0)
	{
		return NULL;
	}
	else if (hash == NULL)
	{
		hash = &djb2_hash;
	}

	table = malloc(sizeof(struct hashtable));
	if (table == NULL)
	{
		return NULL;
	}

	table->size = size;
	table->table = malloc(sizeof(struct linkedlist*) * table->size);

	/* set all table entries to NULL before use.  NULL specifies an empty bucket. */
	for (i = 0; i < table->size; i++)
	{
		table->table[i] = NULL;
	}

	table->hash = hash;

	return table;
}

uint64_t djb2_hash(char* key)
{
	char c;
	uint64_t digest;

	digest = 5381;

	while((c = *key ++))
	{
		digest = ((digest << 5) + digest) + c;
	}

	return digest;
}

int put_entry(struct hashtable* table, char* key, void* data)
{
	uint64_t index;
	struct __key_pair* entry;

	if (table == NULL)
	{
		return -1;
	}
	else if (data == NULL || data == NULL)
	{
		return -2;
	}
	
	entry = __create_key_pair(key, data);

	index = -1;
	index = table->hash(key) % table->size;

	if (table->table[index] == NULL)
	{
		table->table[index] = makeList();
	}

	append(table->table[index], entry);

	return 0;
}

void* get_entry(struct hashtable* table, char* key)
{
	int i;
	struct linkedlist* list;
	uint64_t index;

	if (table == NULL)
	{
		return NULL;
	}
	else if (key == NULL)
	{
		return NULL;
	}

	index = table->hash(key) % table->size;

	if (table->table[index] == NULL)
	{
		return NULL;
	}

	list = table->table[index];

	for (i = 0; i < getLength(list); i++)
	{
		struct __key_pair* pair;

		pair = (struct __key_pair*) get(list, i);

		if (pair != NULL && strcmp(key, pair->key) == 0)
		{
			return ((struct __key_pair*) get(list, i))->obj;
		}
	}

	return NULL;
}
