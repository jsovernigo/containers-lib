#include "hashtable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TESTS 10000

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

	table = hastable_make(TESTS*2, &djb2_hash);

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
		hastable_get(table, keys[i], values[i]);
		puts("done");
	}

	for (i = 0; i < TESTS; i++)
	{
		int* val;

		val = ((int*) hashtable_get(table, keys[i]));
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

		val = ((int*) hashtable_remove(table, keys[i]));
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
		free(val);
		free(keys[i]);
	}

	printf("Expecting NULL (0x0): %p\n", get_entry(table, "NO KEY HERE"));

	free(values);
	free(keys);

	hashtable_destroy(table, &free);

	return 0;
}
