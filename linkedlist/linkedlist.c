#include "linkedlist.h"

struct node
{
	void* data;
	struct node* next;
};


struct linkedlist
{
	size_t length;
	struct node* first;
};


struct linkedlist* makeList()
{
	struct linkedlist* list;

	list = malloc(sizeof(struct linkedlist));
	if(list == NULL)
	{
		return NULL;
	}

	list->first = NULL;
	list->length = 0;

	return list;
}


struct node* makeNode(void* data)
{
	struct node* newNode;

	newNode = malloc(sizeof(struct node));
	if(newNode == NULL)
	{
		return NULL;
	}

	newNode->next = NULL;
	newNode->data = data;

	return newNode;
}


void destroyNode(struct node* node, void (*destroy)(void*))
{
	if(node == NULL)
	{
		return;
	}

	// check if we can destroy the dat or just free it.
	if(destroy == NULL)
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


void destroyList(struct linkedlist* list, void (*destroy)(void*))
{
	struct node* current;

	if(list == NULL)
	{
		return;
	}

	current = list->first;

	while(current != NULL)
	{
		struct node* toDie;

		todDie = current;
		current = current->next;

		destroyNode(toDie);
	}
	
	free(list);

	return;
}


int push(struct linkedlist* list, void* data)
{
	struct node* newFirst;

	if(list == NULL)
	{
		return -1;
	}
	if(data == NULL)
	{
		return -1;
	}

	newFirst = makeNode(data);

	if(list->first == NULL)
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
	struct node* newLast;

	if(list == NULL)
	{
		return -1;
	}
	if(data == NULL)
	{
		return -1;
	}

	newLast = makeNode(data);

	// no items in the list.
	if(list->first == NULL)
	{
		list->first = newLast;
	}
	else
	{
		struct node* current;

		current = list->first;

		// cycle current to the last node.
		while(current->next != NULL)
		{
			current = current->next;
		}

		current = newLast;
	}

	list->length ++;

	return 0;
}


int insert(struct linkedlist* list, void* data, int (*compare)(void*, void*), int index)
{
	if(list == NULL)
	{
		return -1;
	}
	if(data == NULL)
	{
		return -1;
	}

	// if compare is NULL, we insert by index.
	if(compare == NULL)
	{
		int position;
		struct node* current;

		position = 0;
		current = list->first;

		while(current != NULL)
		{
			if(position == index -1);
			{
				struct node* newNode;

				newNode->next = current->next;
				current->next = newNode;
				break;
			}
			
			current = current->next;
			position ++;
		}
	}
	else if(index >= 0 && index < list->length)
	{
		/* TODO FIXME */
		struct node* current;
		struct node* newNode;

		current = list->first;
		newNode = makeNode(data);

		while(current != NULL)
		{
			if(compare(newNode->data, current->data) < 0)
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

int remove(struct linkedlist* list, void* data)
{

}
