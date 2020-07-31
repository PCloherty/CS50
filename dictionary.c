// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "dictionary.h"
#include <string.h>
#include <ctype.h>
#include <strings.h>

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
const unsigned int N = 1;

// Hash table
node *table[N];

int count = 0;


// Returns true if word is in dictionary else false
bool check(const char *word)
{//4th
    // TODO
    
    char copy[LENGTH+1];
    strcpy(copy,word);
    for (int i = 0;copy[i]!='\0';i++)
    {
        if(isupper(copy[i]))
        {
            copy[i]=tolower(copy[i]);
        }    
    }
    int index = hash(word);
    node *pointer = table[index];
    printf("%s : ",pointer->word  );
    while (pointer !=NULL)
    {
        if (strcasecmp(word, pointer->word)==0)
        {
            return true;
        }
        pointer = pointer->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{//2nd
//djb2 algerithm found at
//http://www.cse.yorku.ca/~oz/hash.html
//edited for my variables
        unsigned long value = 5381;
        int c=0;

        while (c == *word++)
            value = ((value << 5) + value) + c;

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
    node *n = malloc(sizeof(node));
    while(fscanf(dictionary_ptr,"%s",word) !=EOF)
    {
        //node *n = malloc(sizeof(node));
        if (n==NULL){
            return false;
        }
        strcpy(n->word, word);
        int index = hash(word);
        if (table[index]==NULL)
        {
            //n->next=NULL;
            table[index]=n;
        }
        else
        {
            n->next= table[index]->next;
            table[index]=n;
        }
        count++;
        //free(n);
        
    }
    //free(*n);
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

// Unloads dictionary from memeturning true if successful else false
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
