// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int letter = toupper(word[0]) - 'A';
    for (node *temp = table[letter]; temp != NULL; temp = temp->next)
    {
        if (strcasecmp(temp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        return false;
    }

    char c;
    int counter = 0;
    node *temp = NULL;
    while (fread(&c, sizeof(char), 1, input))
    {
        if (counter == 0)
        {
            temp = malloc(sizeof(node));
            if (temp == NULL)
            {
                return false;
            }
            temp->next = NULL;

            temp->word[counter] = c;
            counter++;
        }
        else if (c != '\n')
        {
            temp->word[counter] = c;
            counter++;
        }

        if(c == '\n')
        {
            temp->word[counter] = '\0';
            counter = 0;

            int hash = toupper(temp->word[0]) - 'A';

            temp->next = table[hash];
            table[hash] = temp;

            temp = NULL;
        }

    }
    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;

    for (int i = 0; i < N; i++)
    {
        for (node *temp = table[i]; temp != NULL; temp = temp->next)
        {
            count++;
        }
    }

    if (count > 0)
    {
        return count;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    for (int i = 0; i < N; i++)
    {
        node *trash = malloc(sizeof(node));
        for (node *temp = table[i]; temp != NULL; temp = temp->next)
        {
            free(trash);
            trash = temp;
        }
        free(trash);
    }
    return true;
}
