#include <stdio.h>

struct node
{
    struct node *l, *r;
    int num;
};

void insnode(struct node* newnode, struct node** root)
{
    printf("insnode called");
    system("PAUSE");
    if(*root = NULL)
        *root = newnode;
    else
    {
        if(cmpnode(newnode, *root) < 0)
            insnode(newnode, &((*root)->l));
        else
            insnode(newnode, &((*root)->r));
    }
}

void printtree(struct node* n)
{
    if(n->l != NULL)
        printtree(n->l);
    printf("%d ", n->num);
    if(n->r != NULL)
        printtree(n->r);
}

int cmpnode(struct node* a, struct node* b)
{
    printf("comp node called\n");
    system("PAUSE");
    if(a<b)
        return -1;
    else if(a==b)
        return 0;
    else
        return 1;
}

struct node* newnode(int num)
{
    struct node *n = malloc(sizeof(struct node));
    n->num = num;
    n->l = NULL;
    n->r = NULL;
    return n;
}
struct node* removelargest(struct node **ndp)
{
    struct node* temp;
    if((*ndp)->r == NULL)
    {
        temp = *ndp;
        *ndp = (*ndp)->l;
        free(temp);
    }
    else
        return removelargest(&((*ndp)->r));
}
    
void delnode(struct node** n, int value)
{
    struct node* temp;
    if (*n == NULL)
        return;
    
    if((*n)->num == value)
    {
        //no child nodes
        if((*n)->l == NULL && (*n)->r == NULL)
        {    
            free(*n);
            *n = NULL;
        }
        //left child node only
        else if((*n)->r == NULL)
        {
            temp = *n;
            *n = (*n)->l;
            free(temp);
        }
        //right child node only
        else if((*n)->l == NULL)
        {
            temp = *n;
            *n = (*n)->r;
            free(temp);
        }
        //has two child nodes
        else
        {
            temp = *n;
            *n = removelargest(n);
            free(temp);
        }
    }
}

int main()
{
    int temp;
    struct node* newtemp=NULL, *root=NULL;
    root = newnode(0);
    while(1)
    {
        scanf("%d", &temp);
        if(temp < 0)
            break;
        newtemp = newnode(temp);
        printf("%d", newtemp);
        system("PAUSE");
        insnode(newtemp, &root);
    }
    
    printtree(root);

    system("PAUSE");
    return 0;
}
