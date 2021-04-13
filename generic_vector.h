#ifndef INT_VECTOR
#define INT_VECTOR 
#include "generic.h"
#include "Status.h"

typedef void* GENERIC_VECTOR;



GENERIC_VECTOR generic_vector_init_default(Status(*item_assignment)(ITEM*, ITEM),
void (*item_destroy)(ITEM*));

//push_back
Status generic_vector_push_back(GENERIC_VECTOR hVector, ITEM item);

//Accessor functions
int generic_vector_get_size(GENERIC_VECTOR hVector);
int generic_vector_get_capacity(GENERIC_VECTOR hVector);

//clear
//set size to zero so that the vector appears to be empty

//
Boolean generic_vector_empty(GENERIC_VECTOR hVector);

//remove
Status generic_vector_pop_back(GENERIC_VECTOR hVector);

//look at items in the vector
ITEM generic_vector_at(GENERIC_VECTOR hVector, unsigned int index);


void generic_vector_destroy(GENERIC_VECTOR* phVector);

#endif

