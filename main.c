#include <stdio.h>
#include <stdlib.h>
#include "Status.h"
#include "my_string.h"
#include "generic_vector.h"
#include "avl.h"

char play(void);
Status checkWin(MY_STRING word, int size);
void GuessMessage(Message msg, char guess);
Message check_guess(MY_STRING key, char guess,MY_STRING Guessed);
void printGuessed(MY_STRING Guessed);
Status alreadyGuessed(MY_STRING Guessed, char guess);

int main(int argc, char* argv[])
{	
	system("clear");
	

	printf("\t --- EVIL HANGMAN ---\n"); 
	
	
	char play_again;

	do
	{
		play_again = play();

	} while(play_again == 'y' || play_again == 'Y');

	return 0;
}

char play(void)
{
	FILE* fp = fopen("dictionary.txt","r");

	int size;
        char guess;
        int num_guess;
	int win = 0;
	Message msg;
	
        printf("Enter size of word\n");
        scanf("%d",&size);
        ckb();
        printf("Enter how many guesses you would like\n");
        scanf("%d",&num_guess);
        ckb();
        printf("Enter your guess\n");
        scanf("%c",&guess);
	ckb();
	system("clear");
	GENERIC_VECTOR MWL = generic_vector_init_default(my_string_assignment,my_string_destroy);
        MY_STRING word = my_string_init_default();
        MY_STRING CWF = my_string_init_default();
        MY_STRING new_key = my_string_init_default();
	MY_STRING Guessed = my_string_init_default();


        for(int i = 0; i < size; i++)
        {
                my_string_push_back(CWF,'-');
        }


        while(my_string_extraction(word, fp)) //push back all words of desired size into Master Word List
        {
                if(size == my_string_get_size(word))
                {
                        generic_vector_push_back(MWL,word);
                }
        }

	if(size != my_string_get_size(word))
		my_string_destroy(&word);

	
	tNode* root = NULL;
        tNode* max;
        int vsize;
        for(int j = num_guess; j > 0; j--)
        {
                vsize = generic_vector_get_size(MWL);

                for(int i = 0; i < vsize; i++)//iterate through Master Word List, generate key for each word, insert word and correspending key into avl tree
                {
                        word = generic_vector_at(MWL,i);
                        get_word_key_value(CWF,new_key, word,guess);
                        insert(&root,new_key,word);
                }
                //printInOrder(root);
                max = getLargestNode(root, root); // return adress of largest node in avl tree
                swapVector(max, &new_key, &MWL); // swap generic vector in node to preserve data from tree destruction
                destroy(&root);
                root = NULL;
	        printf("Preserved Vector: \n");
                my_string_insertion(new_key,stdout);
                printf("Size is: %d\n",generic_vector_get_size(MWL));
			
		
                my_string_assignment(&CWF,new_key);
		msg = check_guess(CWF,guess,Guessed);
		my_string_push_back(Guessed, guess);
		
		if(checkWin(CWF, size) == SUCCESS) 
                {
                        win = 1;
			break;
                }

		
//		printf("Number of guesses left is : %d\n",j);
		GuessMessage(msg,guess);
		printGuessed(Guessed);
                printf("Enter another guess, you have %d left\n",j);
                scanf("%c",&guess);
		ckb();
		while(alreadyGuessed(Guessed, guess)) // Trap user in a loop until they enter a valid guess
		{
			system("clear");
			printf("Already guessed, try again\n");
			printGuessed(Guessed);
			scanf("%c",&guess);
			ckb();
		}
		system("clear");
		
	}
	if(win == 1)
	{
		printf("you won, the word is: ");//win
		my_string_insertion(CWF,stdout);
		printf("\n");
	}
	else
	{
		printf("You Lost, word was: ");
		my_string_insertion(generic_vector_at(MWL,0),stdout);	
	}
	
//	my_string_destroy(&word);
	my_string_destroy(&CWF);
	my_string_destroy(&new_key);
	my_string_destroy(&Guessed);
        generic_vector_destroy(&MWL);
        destroy(&root);
	fclose(fp);
	
	char play_again;
	printf("Would you like to play again?\n");
	scanf("%c",&play_again);
	return play_again;
}
Status checkWin(MY_STRING word, int size)
{
	int count = 0;

	for(int i = 0; i < size; i++)
	{
		if(*my_string_at(word,i) == '-')
		{
			count++;
		}
	}
	if(count == 0)
	{
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}
Message check_guess(MY_STRING key, char guess, MY_STRING Guessed)
{
	for(int j = 0; j < my_string_get_size(Guessed); j++)
	{
		if(*my_string_at(Guessed,j) == guess)
			return already_guessed;
	}
	for(int i = 0; i < my_string_get_size(key); i++)
	{
		if(*my_string_at(key,i) == guess)
			return Right;
	}
		
	return Wrong;

}
void GuessMessage(Message msg, char guess)
{
	switch(msg)
	{
		case Right:
			printf("Your Guess is Correct!, There is an '%c' in your word\n",guess);
			break;
		case Wrong:
			printf("Your Guess is Incorrect!, There is no '%c' in the word\n",guess); 
			break;
		case already_guessed:
			printf("You already guessed '%c'\n",guess);
	}
	
}
void printGuessed(MY_STRING Guessed)
{
	printf("Already Guessed: ");
	for(int i = 0; i < my_string_get_size(Guessed); i++)
	{
		printf("%c ",*my_string_at(Guessed,i));
	}		
	printf("\n");
}
Status alreadyGuessed(MY_STRING Guessed, char guess)
{
	int size = my_string_get_size(Guessed);
	for(int i = 0; i < size; i++)
	{
		if(*my_string_at(Guessed,i) == guess)
			return SUCCESS;
	}
	return FAILURE;

}
