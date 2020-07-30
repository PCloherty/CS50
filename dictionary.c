// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "dictionary.h"
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];



// Returns true if word is in dictionary else false
bool check(const char *word)
{//4th
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{//2nd
    // TODO
    return 0;
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
        fscanf(dictionary_ptr, "%s", word);
        node *n = malloc(sizeof(node));
        if(n==NULL)
        {
            unload();
            return 1;
        }
        strcpy(n->word,word);
        
        
    }
    fclose(dictionary_ptr);
    return true;
    // TODO
    
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{//3rd
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{//5th
    // TODO
    return false;
}
