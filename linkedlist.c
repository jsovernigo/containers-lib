#include "linkedlist.h"

#include <stdlib.h>

struct __node
{
	void* data;
	struct __node* next;
};


struct linkedlist
{
	size_t length;
	struct __node* first;
};


struct linkedlist* make_list()
{
	struct linkedlist* list;

	list = malloc(sizeof(struct linkedlist));
	if (list == NULL)
	{
		return NULL;
	}

	list->first = NULL;
	list->length = 0;

	return list;
}


struct __node* __make_node(void* data)
{
	struct __node* newNode;

	newNode = malloc(sizeof(struct __node));
	if (newNode == NULL)
	{
		return NULL;
	}

	newNode->next = NULL;
	newNode->data = data;

	return newNode;
}


void __destroy_node(struct __node* node, void (*destroy)(void*))
{
	if (node == NULL)
	{
		return;
	}

	// check if we can destroy the dat or just free it.
	if (destroy == NULL)
	{
		free(node->data);
	}
	else
	{
		destroy(node->data);
	}

	free(node);

	return;
}


void destroy_list(struct linkedlist* list, void (*destroy)(void*))
{
	struct __node* current;

	if (list == NULL)
	{
		return;
	}

	current = list->first;

	while (current != NULL)
	{
		struct __node* toDie;

		toDie = current;
		current = current->next;

		__destroy_node(toDie, destroy);
	}
	
	free(list);

	return;
}


int push(struct linkedlist* list, void* data)
{
	struct __node* newFirst;

	if (list == NULL)
	{
		return -1;
	}
	if (data == NULL)
	{
		return -1;
	}

	newFirst = __make_node(data);

	if (list->first == NULL)
	{
		list->first = newFirst;
	}
	else
	{
		newFirst->next = list->first;
		list->first = newFirst;
	}

	list->length ++;

	return 0;
}

int append(struct linkedlist* list, void* data)
{
	struct __node* newLast;

	if (list == NULL)
	{
		return -1;
	}
	if (data == NULL)
	{
		return -1;
	}

	newLast = __make_node(data);

	// no items in the list.
	if (list->first == NULL)
	{
		list->first = newLast;
	}
	else
	{
		struct __node* current;

		current = list->first;

		// cycle current to the last node.
		while (current->next != NULL)
		{
			current = current->next;
		}

		current->next = newLast;
	}

	list->length ++;

	return 0;
}


int insert(struct linkedlist* list, void* data, int (*compare)(void*, void*), int index)
{
	if (list == NULL)
	{
		return -1;
	}
	if (data == NULL)
	{
		return -1;
	}

	// if compare is NULL, we insert by index.
	if (compare == NULL)
	{
		int position;
		struct __node* current;

		position = 0;
		current = list->first;

		while (current != NULL)
		{
			if (position == index -1)
			{
				struct __node* newNode;

				newNode = __make_node(data);

				newNode->next = current->next;
				current->next = newNode;
				break;
			}
			
			current = current->next;
			position ++;
		}
	}
	else if (index >= 0 && index < list->length)
	{
		/* TODO FIXME */
		struct __node* current;
		struct __node* newNode;

		current = list->first;
		newNode = __make_node(data);

		while (current != NULL)
		{
			if (compare(newNode->data, current->data) < 0)
			{
				
			}
		}

	}
	else
	{
		return -1;
	}

	list->length ++;

	return 0;
}

void* remove_front(struct linkedlist* list)
{
	void* data;
	struct __node* front;
	if (list == NULL)
	{
		return NULL;
	}

	if (list->first == NULL)
	{
		return NULL;
	}

	front = list->first;

	list->first = front->next;

	data = front->data;
	free(front);

	return data;
}

int remove_entry(struct linkedlist* list, void* data)
{
	struct __node* current;

	if (list == NULL)
	{
		return -1;
	}
	if (data == NULL)
	{
		return -1;
	}

	current = list->first;

	if (current->data == data)
	{
		list->first = current->next;
		free(current);

		return 0;
	}

	while (current->next != NULL)
	{
		struct __node* next;
		next = current->next;

		if (next->data == data)
		{
			current->next = next->next;
			free(next);
			return 0;
		}

		current = current->next;
	}

	return -1;
}

void* get(struct linkedlist* list, int index)
{
	int i;
	struct __node* current;

	i = 0;

	if (list == NULL)
	{
		return NULL;
	}

	if (index < 0 || index >= list->length)
	{
		return NULL;
	}

	current = list->first;
	
	while (current != NULL)
	{
		if (index == i)
		{
			return current->data;
		}

		i++;
		current = current->next;
	}

	return NULL;
}

size_t get_length(struct linkedlist* list)
{
	if (list == NULL)
	{
		return -1;
	}

	return list->length;
}
