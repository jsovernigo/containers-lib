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
	struct linkedlist ** buckets;

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

	new_pair->key = malloc(sizeof(char) * (strlen(key) + 1));
	strcpy(new_pair->key, key);

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
	table->buckets = malloc(sizeof(struct linkedlist*) * table->size);

	/* set all table entries to NULL before use.  NULL specifies an empty bucket. */
	for (i = 0; i < table->size; i++)
	{
		table->buckets[i] = NULL;
	}

	table->hash = hash;

	return table;
}

void __destroy_key_pair(struct __key_pair* pair, void (*destroy)(void*))
{
	if (pair == NULL)
	{
		return;
	}

	if (destroy == NULL)
	{
		destroy = &free;
	}

	destroy(pair->obj);
	free(pair->key);
	free(pair);

	return;
}

void destroy_hashtable(struct hashtable* table, void (*destroy)(void*))
{
	int i;

	if (table == NULL)
	{
		return;
	}

	if (destroy == NULL)
	{
		destroy = &free;
	}

	for (i = 0; i < table->size; i ++)
	{
		struct linkedlist * bucket;

		bucket = table->buckets[i];

		if (bucket != NULL)
		{
			struct __key_pair* current_pair;

			current_pair = (struct __key_pair*) remove_front(bucket);

			while (current_pair != NULL)
			{
				__destroy_key_pair(current_pair, destroy);
				current_pair = (struct __key_pair*) remove_front(bucket);
			}
			destroy_list(bucket, &free);
		}
	}

	free(table->buckets);
	free(table);

	return;
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

void* put_entry(struct hashtable* table, char* key, void* data)
{
	uint64_t index;
	struct __key_pair* entry;

	if (table == NULL)
	{
		return NULL;
	}
	else if (data == NULL || data == NULL)
	{
		return NULL;
	}


	index = -1;
	index = table->hash(key) % table->size;

	if (table->buckets[index] == NULL)
	{
		table->buckets[index] = make_list();
	}
	else
	{
		int i;

		/* look through the bucket */
		for (i = 0; i < get_length(table->buckets[index]); i++)
		{
			struct __key_pair* current_pair;

			current_pair = get(table->buckets[index], i);

			/* there is already an entry with this key. */
			if (strcmp(current_pair->key, key) == 0)
			{
				void* old;

				/* replace the current key */
				old = current_pair->obj;
				current_pair->obj = data;

				return old;
			}
		}

	}

	/* if the above loop runs without finding anything, or it was an empty list */
	entry = __create_key_pair(key, data);
	append(table->buckets[index], entry);

	return NULL;
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

	if (table->buckets[index] == NULL)
	{
		return NULL;
	}

	list = table->buckets[index];

	for (i = 0; i < get_length(list); i++)
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
void* unput_entry(struct hashtable* table, char* key)
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

	if (table->buckets[index] == NULL)
	{
		return NULL;
	}

	list = table->buckets[index];

	/* loop through the bucket */
	for (i = 0; i < get_length(list); i++)
	{
		struct __key_pair* current_pair;

		current_pair = (struct __key_pair*) get(list, i);

		if (current_pair != NULL && strcmp(key, current_pair->key) == 0)
		{
			int result;
			void* data;
			result = remove_entry(list, current_pair);

			if (list->first == NULL)
			{
				destroy_list(list, &free);
				
				/* NULL is a condition that indicates an empty bucket. */
				table->buckets[index] = NULL
			}

			/* FIXME this is kinda janky */
			free(current_pair->key);
			data = current_pair->obj;
			free(current_pair);

			return data;
		}
	}

	return NULL;
}

char** get_keys(struct hashtable* table)
{
	size_t i;

	if (table == NULL)
	{
		return NULL;
	}

	for (i = 0; i < table->size; i++)
	{
		/* this is a valid bucket, that has stuff in it */
		if (table->buckets[i] != NULL)
		{
			
		}
	}
}
