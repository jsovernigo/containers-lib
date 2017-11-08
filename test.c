#include "hashtable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TESTS 100

int* ip(int i)
{
	int* ip;

	ip = malloc(sizeof(int));
	*ip = i;

	return ip;
}

int main(int argc, char** argv)
{
	int i;
	int** values;
	char** keys;

	struct hashtable* table;

	table = create_hashtable(TESTS*2, &djb2_hash);

	values = malloc(sizeof(int*) * TESTS);
	keys = malloc(sizeof(char*) * TESTS);

	for (i = 0; i < TESTS; i++)
	{
		char keyi[32];
		values[i] = ip(i);

		sprintf(keyi, "ip%d%c", i, '\0');
		keys[i] = malloc(sizeof(char) * (32 + 1));

		strcpy(keys[i], keyi);

		printf("Putting %s, %d... ", keys[i], *((int*)values[i]));
		put_entry(table, keys[i], values[i]);
		puts("done");
	}

	for (i = 0; i < TESTS; i++)
	{
		int* val;

		val = ((int*) get_entry(table, keys[i]));
		printf("Getting %s, %d... ", keys[i], *((int*)values[i]));
		if (val != NULL)
		{
			printf("(%s:%d)", keys[i], *val);
		}
		else
		{
			printf("(HASH MISS)");
		}
		puts(" done");
	}
	
	for (i = 0; i < TESTS; i++)
	{
		int* val;

		val = ((int*) unput_entry(table, keys[i]));
		printf("Unputting %s, %d... ", keys[i], *((int*)values[i]));

		if (val != NULL)
		{
			printf("unput");
		}
		else
		{
			printf("(HASH MISS)");
		}

		puts(" done");
		free(keys[i]);
	}

	free(values);
	free(keys);

	destroy_hashtable(table, &free);

	return 0;
}
