//Antonio Fluriach
//Assignment 5: Spell Checker
//COP 3502C
//7-24-2010

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//total bytes for each
#define MAXWORDLEN 128
#define FILEPATHLEN 256
#define MAXLINELEN 1024

#define DELIM " \n\r\t~!@#$%^&*()-_=+[]{}\\|;:'\",.<>/?"

struct node
{
    struct node *l, *r;
    char w[MAXWORDLEN];
};

void insert(struct node** crnt, char* str);
int findstr(struct node* crnt, char* str);
int spellcheck(struct node* tree, char *word);
void delete_tree(struct node* root);

int main()
{
    char fpath[FILEPATHLEN], word[MAXWORDLEN], line[MAXLINELEN], *tok;
    FILE *dict, *spdoc;
    struct node* root=NULL;
    int ln, printlabelflag;
    
    //read in dictionary file path
    while(1)
    {
        printf("Dictionary file path, or type \"exit\" to quit: ");
        gets(fpath);
        if(!strcmp(fpath, "exit"))
        {
            printf("Goodbye.\n");
            system("PAUSE");
            return 0;
        }
        dict = fopen(fpath, "r");
        if(dict == NULL)
            printf("Error opening input file \"%s\"\n", fpath);
        else
            break;
    }
    
    //read in spell check document file path
    while(1)
    {
        printf("Input spell check file path, or type \"exit\" to quit: ");
        gets(fpath);
        if(!strcmp(fpath, "exit"))
        {
            printf("Goodbye.\n");
            system("PAUSE");
            return 0;
        }
        spdoc = fopen(fpath, "r");
        if(spdoc == NULL)
            printf("Error opening input file \"%s\"\n", fpath);
        else
            break;
    }
    
    //read in dictionary
    while(!feof(dict))
    {
        fscanf(dict, "%s", word);
        insert(&root, word);
    }
    
    //read through spell check document by line
    for(ln=1; !feof(spdoc);ln++)
    {
        fgets(line, MAXLINELEN, spdoc);
        
        //read through spell check document by token
        //printlabelflag is set to 0 for each line iteration, so the program 
        //only prints the line label once if it finds any misspellings
        for(tok = strtok(line, DELIM), printlabelflag=0; tok != NULL; tok = strtok(NULL, DELIM))
        {
            if(!spellcheck(root, tok))
            {
                if(!printlabelflag)
                {
                    printf("Line %d - ", ln);
                    printlabelflag=1;
                }
                
                printf("%s ", tok);
            }
        }
        if(printlabelflag)
        {
            printf("\n");
        }
    }
    
    delete_tree(root);
    system("PAUSE");
    return 0;
}

void insert(struct node** crnt, char* str)
{
    //crnt node is at the end of a branch; put node here
    if(*crnt == NULL)
    {
        *crnt = malloc(sizeof(struct node));
        (*crnt)->l=NULL, (*crnt)->r=NULL;
        strcpy((*crnt)->w, str);
    }
    //if crnt is not null, go down the l or r branch based on comarison of 
    //crnt's word
    else
    {
        if(strcmp(str, (*crnt)->w) < 0)
        {
            insert(&((*crnt)->l), str);
        }
        else
        {
            insert(&((*crnt)->r), str);
        }
    }
}

int findstr(struct node* crnt, char* str)
{
    if(crnt==NULL)
        return 0;
    else if(!strcmp(crnt->w, str))
        return 1;     
    else return strcmp(str, crnt->w) < 0 ? findstr(crnt->l, str) : findstr(crnt->r, str);
}

int spellcheck(struct node* tree, char *word)
{   
    char lccopy[MAXWORDLEN];
    //if lowercase, only search for lowercase version
    if(islower(word[0]))
        return findstr(tree, word);
    //if uppercase, search for both
    else
    {
        strcpy(lccopy, word);
        lccopy[0] = tolower(lccopy[0]);
        return (findstr(tree, word) || findstr(tree, lccopy));
    }
}

void delete_tree(struct node* root)
{
    if(root->l != NULL)
        delete_tree(root->l);
    if(root->r != NULL)
        delete_tree(root->r);
    free(root);
}
