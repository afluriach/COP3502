#include <stdio.h>
#include "hashtable.h"

struct hnode* create_strhnode(char* s);
int strhash(struct hnode* h);
void print_strhnode(struct hnode* h);

int hnode_strcmp(struct hnode* h1, struct hnode* h2)
{
    return !strcmp(h1->d, h2->d);
}

void strhnode_deleter(struct hnode* h)
{
    free(h->d);
}

int main()
{
    char temp[256];
    struct htable* ht = create_htable(100);
    int i, choice;
    struct hnode* tempnode;
    
    while(1)
    {
        printf("1. Insert string.\n"
               "2. Print table.\n"
               "3. Delete string.\n"
               "4. exit\n");
        fgets(temp, sizeof(temp), stdin);
        choice = atoi(temp);
        if(choice==1)
        {
            printf("string to insert:\n");
            fgets(temp, sizeof(temp), stdin);
            insert_hnode(ht, tempnode=create_strhnode(temp), strhash);
            strhnode_deleter(tempnode);
        }
        if(choice==2)
        {
            print_htable(ht, print_strhnode);
        }
        if(choice==3)
        {
            printf("string to delete:\n");
            gets(temp);
            if(delete_hnode(ht, tempnode=create_strhnode(temp), strhash, hnode_strcmp, strhnode_deleter))
                printf("%s deleted\n", temp);
            else
                printf("%s not deleted\n", temp);
                
            strhnode_deleter(tempnode);
        }
        if(choice==4)
        {
            break;
        }
    }
    
    delete_htable(ht);
    system("PAUSE");
    return 0;
}

void print_strhnode(struct hnode* h)
{
    fputs((const char*) h->d, stdout);
}

struct hnode* create_strhnode(char* s)
{
    struct hnode* h = malloc(sizeof(struct hnode));
    h->d=malloc(strlen(s)+1);
    strcpy(h->d, s);
    h->n = NULL;
}

int strhash(struct hnode* h)
{
    char * s = (char*) h->d;
    char even=0, odd=0;
    int i;
    for(i=0;s[i] != '\0'; i++)
    {
        if(i%2==0)
            even ^= s[i];
        else
            odd ^= s[i];
    }
    return even*odd;
}
