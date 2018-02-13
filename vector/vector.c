/**
 *	Julian Sovernigo
 *	juliansovernigo@gmail.com
 *	this file contains code that allows the instantiation of a vector adt.
 */
#include "vector.h"
#include <stdlib.h>
#include <string.h>

struct vector 
{
	size_t length;
	size_t csize;
	void** contents;
};

struct vector* vector_make() 
{
	struct vector* vec;

	vec = malloc(sizeof(struct vector));
	if (!vec) 
	{
		return NULL;
	}

	vec->csize = 1;
	vec->length = 0;

	vec->contents = malloc(sizeof(void*));
	if (!vec->contents) 
	{
		free(vec);
		return NULL;
	}

	return vec;
}

void vector_destroy(struct vector* vec) 
{
	int i;

	if (vec == NULL) 
	{
		return;
	} 
	else if (!vec->contents) 
	{
		free(vec);
		return;
	}

	for (i = 0; i < vec->length; i++) 
	{
		free(vec->contents[i]);
	}
	free(vec->contents);
	free(vec);

	return;
}

void _vector_expand(struct vector* vector) 
{
	size_t nsize;

	void** ncontents;

	if (!vector || !vector->contents) 
	{
		return;
	}

	// thank you Hugo Klepsch for this idea :)
	nsize = (vector->csize << 1) + 1;
	ncontents = malloc(sizeof(void*) * nsize);
	if (!ncontents) 
	{
		return;
	} 
	else 
	{
		vector->csize = nsize;
	}

	memcpy(ncontents, vector->contents, vector->length);

	free(vector->contents);
	vector->contents = ncontents;

	return;
}

int vector_insert(struct vector* vec, void* v, size_t pos) 
{
	int i;

	if (!vec || !v) 
	{
		return -1;
	} 
	else if (pos > vec->length || pos < 0) 
	{
		return -1;
	}

	if (vec->length == vec->csize) 
	{
		_vector_expand(vec);
	}

	vec->length ++;

	for (i = vec->length - 1; i > pos; i--) 
	{
		vec->contents[i] = vec->contents[i-1];
	}

	vec->contents[pos] = v;
	return 0;
}

int vector_append(struct vector* vec, void* v) 
{
	if (!vec || !v) 
	{
		return -1;
	} 
	else if (vec->length == vec->csize) 
	{ 
		_vector_expand(vec);
	}

	/* we are adding an item to the array... */
	vec->length ++;

	/* adds v to the end of the array */
	vec->contents[vec->length-1] = v;

	return 0;
}

int vector_push(struct vector* vec, void* v) 
{
	if (!vec || !v) 
	{
		return -1;
	} 
	else if (vec->length == vec->csize) 
	{
		_vector_expand(vec);
	}

	vector_insert(vec, v, 0);

	return 0;
}

void* vector_pop(struct vector* vec) 
{
	if (!vec) 
	{
		return NULL;
	} 
	else if (!vec->contents) 
	{
		return NULL;
	}

	return vector_remove(vec, 0);
}

void* vector_remove(struct vector* vec, size_t pos) 
{
	int i;
	void* p;

	if (!vec) 
	{
		return NULL;
	} 
	else if (!vec->contents) 
	{
		return NULL;
	} 
	else if (pos < 0 || pos >= vec->length) 
	{
		return NULL;
	}

	p = vec->contents[pos];

	for (i = pos; i < vec->length - 1; i++) 
	{
		vec->contents[i] = vec->contents[i + 1];
	} 
	vec->contents[vec->length - 1] = NULL;
	vec->length --;

	return p;
}

void* vector_at(struct vector* vec, size_t i) 
{
	if (!vec || i > vec->length || i < 0) 
	{
		return NULL;
	}

	return vec->contents[i];
}

size_t vector_length(struct vector* vec)
{
	if (!vec)
	{
		return -1;
	}

	return vec->length;
}
