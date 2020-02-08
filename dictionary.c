// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <inttypes.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100;

// Hash table
node *table[N];

//set counters
int word_counter = 0;


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    //return true if the word is in the dictionary
    //should be case insensitive

    //lowercase the incomming word to confirm same hash
    int len = strlen(word);
    char word_check[len + 1];
    for (int i = 0; i < len + 1; i++)
    {
        word_check[i] = tolower(word[i]);
    }
 
    //hash word to obtain hash value
    int h = hash(word_check);
    
    //create cursor
    node *cursor = table[h];
    
    //access linked list at that index in the hash table
    while (cursor != NULL)
    {
        //traverse linked list, looking for the word using (strcasecmp)
        if (strcasecmp(cursor->word, word_check) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    //input: word with alphabetical and possibly apostrophies
    //ouput: nuumerical index between 0 and N - 1, inclusive
    //shouud be deterministic

    //Hash function is 'Shift-Add-XOR hash', from https://eternallyconfuzzled.com/hashing-c-introduction-to-hashing/
    unsigned h = 0;
    int len = strlen(word);

    for (int i = 0; i < len; i++)
    {
        h ^= (h << 5) + (h >> 2) + word[i];
    }
    h = h % 100;
    return h;

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO

    //set hash table headers to null
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    //open dictionary
    FILE *dictionary_ptr = fopen(dictionary, "r");
    if (dictionary_ptr == NULL)
    {
        return false;
    }

    char new_word[LENGTH + 1];

    //read strings froms file one at a time
    //fscanf will return EOF once it reaches end of file
    while (fscanf(dictionary_ptr, "%s", new_word) != EOF)
    {
        //malloc *node for each new word
        node *node1 = malloc(sizeof(node));
        if (node1 == NULL)
        {
            unload();
            return false;
        }

        //copy word into node1
        strcpy(node1->word, new_word);
        node1->next = NULL;

        //hash function takes a string and returns an index
        int i = hash(new_word);

        //add words to hash table
        if (table[i] == NULL)
        {
            table[i] = node1;
        }
        else
        {
            //set node1 pointer to next in list
            node1->next = table[i];
            //reset head to point to node1
            table[i] = node1;
        }
        
        word_counter++;
    }
    
    fclose(dictionary_ptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (word_counter > 0)
    {
        return word_counter;
    }

    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    //go through hash tables with cursor and free all memory

    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }

        free(cursor);
    }
    return true;
}

