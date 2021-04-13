#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "my_string.h"
#include "generic_vector.h"

tNode* newNode(MY_STRING key, MY_STRING word)
{
	tNode* temp = (tNode*)malloc(sizeof(tNode));
	if (temp == NULL)
	{
		printf("Failed to allocate Node\n");
		return NULL;
	}
	temp->key = my_string_init_default();
	my_string_assignment(&(temp->key),key); // create deep copy of key and store it in Node->key
	temp->word_list = generic_vector_init_default(my_string_assignment, my_string_destroy);
	generic_vector_push_back(temp->word_list, word); // push word into generic vector
	temp->right = NULL;
	temp->left = NULL;
	temp->height = 1; //initial node height is 1
	return temp;
}
void insert(tNode** node, MY_STRING key, MY_STRING word)
{
	if (*node == NULL)
	{
		*node = newNode(key,word);
		return;
	}
	
	int compare = my_string_compare(key, (*node)->key); // negative if right is bigger, positive is left is bigger, 0 if same
	if (compare > 0) // key > node->key
		insert(&((*node)->right), key, word);

	else if (compare < 0) // key < node->key
		insert(&((*node)->left), key, word);
	else	//node->key == key	
		generic_vector_push_back((*node)->word_list,word);
	
	//update node height
	(*node)->height = 1 + getMax(getHeight((*node)->left), getHeight((*node)->right));
	
	//Calculate Balance Factor
	int balance = getBalance(*node);

	//preform rotations if node is unbalanced

	//Left Left Case
	if (balance > 1 && my_string_compare(key, (*node)->left->key) < 0)
	{
		*node = RightRotate(*node);
		return;
	}

	//Right Right Case
	if (balance < -1 && my_string_compare(key, (*node)->right->key) > 0)
	{
		*node = LeftRotate(*node);
		return;
	}

	//Right Left Case
	if (balance < -1 && my_string_compare(key, (*node)->right->key) < 0) //if (balance < -1 && key < node->rChild->key)
	{
		(*node)->right = RightRotate((*node)->right);
		*node = LeftRotate(*node);
		return;
	}

	//Left Right Case
	if (balance > 1 && my_string_compare(key, (*node)->left->key) > 0) //   if (balance > 1 && key > node->lChild->key)
	{
		(*node)->left = LeftRotate((*node)->left);
		*node = RightRotate(*node);
		return;
	}
	return;
}
int getHeight(tNode* x)
{
	if (x == NULL)
		return 0;
	else
		return x->height;
}
int getBalance(tNode* x)
{
	if (x == NULL)
		return 0;
	else
		return getHeight(x->left) - getHeight(x->right);
}
int getMax(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

tNode* LeftRotate(tNode* x)
{
	tNode* y = x->right;
	tNode* t2 = y->left;

	//preform rotation
	y->left = x;
	x->right = t2;
	
	//update node height
	x->height = 1 + getMax(getHeight(x->left), getHeight(x->right));
	y->height = 1 + getMax(getHeight(y->left), getHeight(y->right));

	return y;
}
tNode* RightRotate(tNode* y)
{
	tNode* x = y->left;
	tNode* t2 = x->right;

	//preform rotation
	x->right = y;
	y->left = t2;

	//update node height
	y->height = 1 + getMax(getHeight(y->left), getHeight(y->right));
	x->height = 1 + getMax(getHeight(x->left), getHeight(x->right));

	return x;
}
void printInOrder(tNode* node)
{
	if (node == NULL)
		return;
	
	printInOrder(node->left);
	my_string_insertion(node->key, stdout);
	printf("Words in Keys Node: %d\n",generic_vector_get_size(node->word_list));
	printInOrder(node->right);
}
void destroy(tNode** node)
{
        if(*node == NULL)
                return;
    
        destroy(&(*node)->left);
        destroy(&(*node)->right);
	my_string_destroy(&((*node)->key)); // destroy key
	generic_vector_destroy(&((*node)->word_list)); // destroy generic_vector word_list
        free(*node);
}
tNode* getLargestNode(tNode* node, tNode* max)
{
	if(node == NULL)
		return max;

	max = getLargestNode(node->left,max);
	if(generic_vector_get_size(node->word_list) > generic_vector_get_size(max->word_list))
		max = node;
	max = getLargestNode(node->right,max);
	return max;
}
void swapVector(tNode* node, MY_STRING* key, GENERIC_VECTOR* MWL)
{
	if(node == NULL)
	{
		return;
	}
	my_string_assignment(key,node->key);

	if(*MWL != NULL)
	{
		generic_vector_destroy(MWL);
		*MWL = NULL;
	}
	*MWL = node->word_list;
	node->word_list = NULL;
	return;
}
