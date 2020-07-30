// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "dictionary.h"
#include <string.h>
#include <ctype.h>
//#include <srings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
//first letter
//first two letters
//math using all letters
const unsigned int N = 10;

// Hash table
node *table[N];

int count = 0;


// Returns true if word is in dictionary else false
bool check(const char *word)
{//4th
    // TODO
    char *caseCopy = malloc(strlen(word));
    strcpy(caseCopy,word);
    int tolower(int caseCopy);
    int index = hash(caseCopy);
    node *pointer = table[index];
    while (pointer !=NULL)
    {
        if (strcmp(pointer -> word, caseCopy)==0)
        {
            free(caseCopy);
            return true;
        }
        pointer = pointer-> next;
    }
    free(caseCopy);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{//2nd
//http://www.cse.yorku.ca/~oz/hash.html djb2

        unsigned long value = 5381;
        int c=0;

        while (c == *word++)
            value = ((value << 5) + value) + c; /* hash * 33 + c */

        return value % N;
    

    // TODO
    //return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{//1st
    FILE *dictionary_ptr = fopen(dictionary, "r");
    if (dictionary_ptr == NULL)
    {
        return false;
    }
    char word[LENGTH+1];
    while(fscanf(dictionary_ptr,"%s",word) !=EOF)
    {
        node *n = malloc(sizeof(node));
        strcpy(n->word,word);
        int index = hash(word);
        if (table[index]==NULL)
        {
            n->next=NULL;
            table[index]=n;
        }
        else
        {
            n-> next= table[index]-> next;
            table[index]=n;
        }
        count++;
    }
    fclose(dictionary_ptr);
    return true;
    // TODO
    
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{//3rd
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{//5th
    // TODO
    for( unsigned int i = 0 ; i < N; i++)
    {
    node *pointer=table[i];
    while(pointer !=NULL)
    {
        node *temp= pointer;
        pointer = pointer->next;
        free(temp);
    }
    }
    return true;
}
