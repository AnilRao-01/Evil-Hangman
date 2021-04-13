#include <stdlib.h>
#include "generic_vector.h"

//The KNOWN TYPE
struct vector
{
	Status(*item_assignment)(ITEM*, ITEM);
	void (*item_destroy)(ITEM*);
	int size;
	int capacity;
	ITEM* data;
};
typedef struct vector Vector;

GENERIC_VECTOR generic_vector_init_default(Status(*item_assignment)(ITEM*, ITEM),
	void(*item_destroy)(ITEM*))
{
	int i;
	Vector* pVector = (Vector*) malloc(sizeof(Vector));
	if (pVector != NULL)
	{
		//worked
		pVector->item_assignment = item_assignment;
		pVector->item_destroy = item_destroy;
		pVector->size = 0;
		pVector->capacity = 1;
		pVector->data = (ITEM*)malloc(sizeof(ITEM) * pVector->capacity);
		if (pVector->data == NULL)
		{
			free(pVector);
			return NULL;
		}
		for (i = 0; i < pVector->capacity; i++)
		{
			pVector->data[i] = NULL;
		}
	}
	return (GENERIC_VECTOR)pVector;
}

Status generic_vector_push_back(GENERIC_VECTOR hVector, ITEM item) 
{
	Vector* pVector = (Vector*) hVector;
	ITEM* temp;
	int i;
	Status my_status;

	if (pVector->size >= pVector->capacity) //no room
	{
		temp = (ITEM*) malloc(sizeof(ITEM)* pVector->capacity * 2);
		if (temp == NULL)
		{
			return FAILURE;
		}
		for (i = 0; i < pVector->size; i++)
		{
			temp[i] = pVector->data[i];
		}  //BUG IS HERE.  We have copied all the old data but what is in the 
		   //rest of the array?  We expect it to be filled with NULL values but
		   //they are uninitialized instead.
		for (i; i < pVector->capacity * 2; i++)
		{
			temp[i] = NULL;
		}
		free(pVector->data);
		pVector->data = temp;
		pVector->capacity *= 2;
	}
	//pVector->data[pVector->size] = item;
	my_status = pVector->item_assignment(&(pVector->data[pVector->size]), item);
	if (my_status == FAILURE)
	{
		return FAILURE;
	}
	pVector->size++;
	return SUCCESS;
}

int generic_vector_get_size(GENERIC_VECTOR hVector)
{
	Vector* pVector = (Vector*)hVector;
	return pVector->size;
}
int generic_vector_get_capacity(GENERIC_VECTOR hVector)
{
	Vector* pVector = (Vector*)hVector;
	return pVector->capacity;
}

Boolean generic_vector_empty(GENERIC_VECTOR hVector)
{
	Vector* pVector = (Vector*)hVector;

	return (Boolean) (pVector->size == 0);
}

ITEM generic_vector_at(GENERIC_VECTOR hVector, unsigned int index)
{
	Vector* pVector = (Vector*)hVector;

	if (index >= pVector->size) //out of bounds!
	{
		//printf("vector subscript out of range.\n");
		return NULL;
	}

	return (pVector->data[index]);
}

Status generic_vector_pop_back(GENERIC_VECTOR hVector)
{
	Vector* pVector = (Vector*)hVector;

	if (pVector->size == 0)
	{
		return FAILURE;
	}
	pVector->item_destroy(&(pVector->data[pVector->size - 1]));
	pVector->size--;
	return SUCCESS;
}

void generic_vector_destroy(GENERIC_VECTOR* phVector)
{
	
	Vector* pVector = (Vector*) *phVector;
	if(pVector == NULL)
	{
		return;
	}
	int i;

	for (i = 0; i < pVector->size; i++)
	{
		pVector->item_destroy(&(pVector->data[i]));
	}
	free(pVector->data);
	free(pVector);
	*phVector = NULL;
}
