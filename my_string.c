#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

typedef struct my_string
{
	int size;
	int capacity;
	char* data;

}My_string;

MY_STRING my_string_init_default(void)
{
	My_string* pMy_string = (My_string*)malloc(sizeof(My_string));
	if(pMy_string == NULL)
	{
		printf("Failed to Allocate\n");
		return NULL;
	}
	pMy_string->size = 0;
	pMy_string->capacity = 7;
	pMy_string->data = (char*)malloc(sizeof(char)*pMy_string->capacity);
	if(pMy_string->data == NULL)
	{
		free(pMy_string);
		return NULL;
	}
	return (MY_STRING) pMy_string;
}

void my_string_destroy(ITEM* pItem)
{
	My_string* pMy_string = (My_string*) *pItem;
	if(pMy_string == NULL)
	{
		return;
	}
	free(pMy_string->data);
	free(pMy_string);

	*pItem = NULL;
	return;
}

MY_STRING my_string_init_c_string(const char* c_string)
{
	int length = 0;
	for(int i = 0; c_string[i] != '\0'; i++)
	{
		length++;
	}
//	printf("Length is: %d\n",length);
	My_string* pMy_string = (My_string*)malloc(sizeof(My_string));
	if(pMy_string == NULL)
	{
		printf("Failed to allocate\n");
		return NULL;
	}
	pMy_string->size = length;
	pMy_string->capacity = ++length;
	pMy_string->data = (char*)malloc(sizeof(char)*pMy_string->capacity);
	if(pMy_string->data == NULL)
	{
		printf("Failed to allocate\n");
		free(pMy_string);
		return NULL;
	}	
	for(int i = 0;i<length; i++)
	{
		pMy_string->data[i] = c_string[i];
		
	}
	return (MY_STRING) pMy_string;
}

 int my_string_get_size(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*) hMy_string;
	return pMy_string->size;	
}

int my_string_get_capacity(MY_STRING hMy_string)
{	
	My_string* pMy_string = (My_string*) hMy_string;
	return pMy_string->capacity;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
	My_string* pLeft_string = (My_string*) hLeft_string;
	My_string* pRight_string = (My_string*) hRight_string;
	int length_left = 0,length_right = 0;
	length_left = my_string_get_size(pLeft_string);
	length_right = my_string_get_size(pRight_string);
	
	if(length_left > length_right)
	{
		return 1;
	}		
	else if(length_left < length_right)
	{
		return -1;
	}
	else if(length_left == length_right)
	{
		for(int i = 0; i < length_left;i++)
		{
			if(pLeft_string->data[i] > pRight_string->data[i])
			{
				return 1;
			}
		
			else if(pLeft_string->data[i] < pRight_string->data[i])
			{
				return -1;
			}
		}	
	}
	
	return 0;
}
Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
	My_string* pMy_string = (My_string*)hMy_string;
	pMy_string->size = 0;
	char temp;
	int a;
	a = fscanf(fp, "%c", &temp);
	while (a!= EOF && (temp == ' ' || temp == '\n' || temp == '\t'))
	{
		a = fscanf(fp, "%c", &temp);
	}
	while (a != EOF && !(temp == ' ' || temp == '\n' || temp == '\t'))
	{
		if (pMy_string->size >= pMy_string->capacity)
		{
			char* temple = (char*)malloc(sizeof(char) * pMy_string->capacity * 2);
			if (temple == NULL)
			{
				return FAILURE;
			}
			pMy_string->capacity *= 2;
			for (int i = 0; i < pMy_string->size; i++)
			{
				temple[i] = pMy_string->data[i];
			}
			free(pMy_string->data);
			pMy_string->data = temple;
		}
		 pMy_string->data[pMy_string->size] = temp;
                 pMy_string->size++;
		 a = fscanf(fp, "%c", &temp);
	}
	if(pMy_string->size == 0)
	{
		return FAILURE;
	}
	else
	{
		if(a != EOF)
		{
			ungetc(temp,fp);	
		}
		return SUCCESS;
	}

}
Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
	My_string* pMy_string = (My_string*)hMy_string;
	for (int i = 0; i < pMy_string->size; i++)
	{
		fprintf(fp, "%c", pMy_string->data[i]);
	}
	printf("\n");
	return SUCCESS;
	
}

Status my_string_pop_back(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*) hMy_string;
	if(pMy_string->size == 0)
	{
		return FAILURE;
	}
	pMy_string->size--;
	return SUCCESS;
}

Status my_string_push_back(MY_STRING hMy_string, char item)
{
	My_string* pMy_string = (My_string*) hMy_string;
	if(pMy_string->size >= pMy_string->capacity)
	{
		char* temp = (char*)malloc(sizeof(char)*pMy_string->capacity*2);
		if(temp == NULL)
		{
			return FAILURE;
		}
		pMy_string->capacity*=2;
		for(int i = 0; i < pMy_string->size; i++)
		{
			temp[i] = pMy_string->data[i];
		}
		free(pMy_string->data);
		pMy_string->data = temp;		
	}
	pMy_string->data[pMy_string->size] = item;
	pMy_string->size++;
	return SUCCESS;
}

char* my_string_at(MY_STRING hMy_string, int index)
{
	My_string* pMy_string = (My_string*) hMy_string;
	if(index < 0 || index > pMy_string->size)
	{
		return NULL;
	}
	else
	{
		return &(pMy_string->data[index]);
	}
}
char* my_string_c_str(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*) hMy_string;
	if(pMy_string->size >= pMy_string->capacity)
	{
		char* temp = (char*)malloc(sizeof(char)*(++pMy_string->capacity));
		if(temp == NULL)
		{
			printf("Failed to allocate\n");
			exit(-1);
		}
		for(int i = 0;i < pMy_string->size;i++)
		{
			temp[i] = pMy_string->data[i];
		}
		free(pMy_string->data);
		pMy_string->data = temp;
	}
	pMy_string->data[pMy_string->size] = '\0';
	return pMy_string->data;
}
Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
	My_string* pMy_string = (My_string*) hResult;
	My_string* rMy_string = (My_string*) hAppend;
	
	int size = pMy_string->size + rMy_string->size;
	if(size >= pMy_string->capacity)
	{
		char* temp = (char*)malloc(sizeof(char)*pMy_string->capacity*2);
		if(temp == NULL)
		{
			return FAILURE;
		}
		pMy_string->capacity *= 2;
		for(int i = 0; i < pMy_string->size;i++)
		{
			temp[i] = pMy_string->data[i];
		}
		free(pMy_string->data);
		pMy_string->data = temp;
	}	
	for(int i = 0; i < rMy_string->size; i++)
	{
		pMy_string->data[pMy_string->size] = rMy_string->data[i];
		pMy_string->size++;
	}
	return SUCCESS;	
}
Boolean my_string_empty(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*) hMy_string;
	if(pMy_string->size == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}
Status my_string_assignment(ITEM* pLeft, ITEM Right)
{
	int size = my_string_get_size(Right);
	if(*pLeft == NULL)
	{
		*pLeft = my_string_init_default();
	}
	else
	{
		while(my_string_empty(*pLeft) == FALSE)
		{
			my_string_pop_back(*pLeft);
		}
	}
	for(int i = 0; i < size; i++)
	{
		my_string_push_back(*pLeft,*my_string_at(Right,i));
	}
	return SUCCESS;
}
Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess)
{
	while(!my_string_empty(new_key))
	{
		my_string_pop_back(new_key);
	}
	int size = my_string_get_size(word);
		
	for(int i = 0; i < size; i++)
	{
		if(*(my_string_at(word,i)) == guess)
		{
			my_string_push_back(new_key,guess);
		}
		else
		{
			my_string_push_back(new_key,*(my_string_at(current_word_family,i)));
		}
	}
	return SUCCESS;
}
void ckb(void)
{
    char c;

    do  
    {   
        scanf("%c", &c);
    } while (c != '\n');
}

