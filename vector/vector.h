/**
 *	Julian Sovernigo
 *	juliansovernigo@gmail.com
 *	this file contains code that allows the instantiation of a vector adt.
 */
#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdlib.h>


/**
 *	vector_make
 *	makes a new vector to be used to store things.
 *	IN:			size		- the size of the vector to be created.  Note that this is more
 *							  like a suggestion, as the size is variable.  It can be used
 *							  to speed up the insertion of initial elements into the vector
 *	OUT:		a new vector that you can use to store anything.
 *	POST:		a new vector has been returned.  Use vector_destroy when you're done.
 *	ERROR:		malloc fails
 */
struct vector* vector_make();

/**
 * 	vector_destroy
 * 	destroys a vector struct completely, so that no memory leaks do not occur.
 * 	IN:			vec			- a vector struct to be destroyed
 *	OUT:		void
 *	POST:		vec has been deallocated, so use it with care.
 *	ERROR:		vec is a dangling pointer.
 */
void vector_destroy(struct vector* vec);

/**
 *	_vector_expand
 *	doubles the size of a vector (reallocates the array.)
 *	IN:			vector		- the vector that will have its size doubled (usually the result
 *							  of an add to an already full array.
 *	OUT:		void
 *	POST:		vector->csize has been increased, and the array has been doubled in length
 *				and also copied over so as to perserve its information
 *	ERROR:		vector or vector->contents are null.
 */
void _vector_expand(struct vector* vector);

/**
 *	vector_insert
 *	inserts a void pointer at location pos in the vector.  This is used by other functions
 *	also so as to provide a universal interface for those other functions.
 *	IN:			vec			- the vector to be added to
 *				v			- the void pointer we want to add
 *				pos			- the position we want to add it to.
 *	OUT:		-1 on error, 0 on success, positive error code on failure
 *	POST:		v has been added to vec, and vec->length has increased.
 *	ERROR:		any are null, pos is invalid.
 */
int vector_insert(struct vector* vec, void* v, size_t pos);

/**
 *	vector_append
 *	appends the void pointer v to the vector vec.
 *	IN:			vec			- the vector to be added to
 *				v			- the void pointer we want to add to vec.
 *	OUT:		-1 on error, 0 on success, positive error code on failure
 *	POST:		v has been added to vec.
 *	ERROR:		vec or v are null
 */
int vector_append(struct vector* vec, void* v);

/**
 *	vector_push
 *	pushes void pointer v to the front of vector vec.
 *	IN:			vec			- the vector to be added to
 *	    		v			- the void pointer that will be added to the vector vec.
 *	OUT:		-1 on error, 0 on success, positive error code on failure.
 *	POST:		v has been added to vec, and vec->length has been updated.
 *	ERROR:		vec or v are null or dangling.
 */
int vector_push(struct vector* vec, void* v);

/**
 *	vector_pop
 *	returns the void pointer at vec->contents[0], and also removes it from the vector.
 *	IN:			vec			- the vector to be popped from
 *	OUT:		the void pointer that (was) at vec->contents[0]
 *	POST:		vec->contents has been updated; vec->length has been updated;
 *				vec->contents[0] returned.
 *	ERROR:		vec is null or has no items to be returned.
 */
void* vector_pop(struct vector* vec);

/**
 *	vector_remove
 *	removes the void pointer and returns it as it occurs in vec->contents[i]
 *	IN:			vec			- the vector that will be modified
 *				i			- the index that will be selected
 *	OUT:		returns the item that was formerly at position i in the vector.
 *	POST:		vec is shorter, and a void pointer has been returned.
 *	ERROR:		vec is null, i is invalid.
 */
void* vector_remove(struct vector* vec, size_t i);

/**
 * 	vector_at
 * 	returns the member of the vector contents at index i, or NULL on error.
 * 	IN:			vec			- the vector the be scanned.
 * 				i			- the integer index.
 * 	OUT:		returns the void pointer at vec->contents[i], or null.
 * 	POST:		value returned.
 * 	ERROR:		vec is null, or i is greater than the size of the vector.
 */
void* vector_at(struct vector* vec, size_t i);

/**
 *
 */
size_t vector_length(struct vector* vec);

#endif
