// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

void free_list(node *p);

// Choose number of buckets in hash table
const unsigned int N = 13579;//26

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    for (node *p = table[hash(word)]; p != NULL; p=p->next)
    {
        if (strcasecmp(p->word, word) == 0)
            return true;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int ctr = 0;
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        ctr += toupper(word[i]) - 'A';
    }
    return ctr % N;

    //return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL) return false;
    for(;;)
    {
        //读取单词到word
        char word[LENGTH];
        if(fscanf(fp, "%s", word)==-1) break;

        //导入哈希表
        if(table[hash(word)] == NULL) table[hash(word)] = (node *)malloc(sizeof(node));
        for(node *new = table[hash(word)];;)
        {
            if(new->word[0] == 0)
            {
                strcpy(new->word, word);
                new->next = (node *)malloc(sizeof(node));
                break;
            }
            new = new->next;
        }

    }
    fclose(fp);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int ctr = 0;
    for (int i = 0; i < N; i ++)
    {
        for (node *p = table[i];p!=NULL;p = p->next)
        {
            if(strcmp(p->word, "") != 0) ctr++;
        }
    }
    return ctr;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i ++)
    {
        free_list(table[i]);
        //for (node *p = table[i]; p!=NULL; p = p->next)
        //{
        //    node *tmp = p;
        //    free(tmp);
        //    if(i == N - 1) free(p->next);
        //}
        //if (table[i]!=NULL) return false;
    }
    return true;

}
void free_list(node *p)
{
    if(p == NULL) return;
    free_list(p->next);
    free(p);
}