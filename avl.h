#ifndef AVL_TREE
#define AVL_TREE
#include "my_string.h"
#include "generic_vector.h"

typedef struct tree tNode;

struct tree
{
        MY_STRING key;
	GENERIC_VECTOR word_list;
        tNode* left;
        tNode* right;
        int height;
};

tNode* newNode(MY_STRING key, MY_STRING word);

int getHeight(tNode* x); 

int getBalance(tNode* x); 

int getMax(int a, int b); 

tNode* LeftRotate(tNode* y); 

tNode* RightRotate(tNode* x); 

void insert(tNode** node, MY_STRING key, MY_STRING word);

void printInOrder(tNode* node);

tNode* getLargestNode(tNode* node, tNode* max);

void swapVector(tNode* node, MY_STRING* key, GENERIC_VECTOR* MWL);

void destroy(tNode** node);


#endif
