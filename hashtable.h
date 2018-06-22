struct hnode
{
    struct hnode* n;
    void* d;
};

struct htable
{
    int size, nelem;
    struct hnode **arr;
};

struct htable* create_htable(int size);
void delete_hnodechain(struct hnode* h);
void delete_htable(struct htable* h);
void insert_hnode(struct htable* ht, struct hnode* hn, int (*hashfunc) (struct hnode*));
void print_htable(struct htable* h, void (*printfunc) (struct hnode*));
struct hnode* lookup_hnode(struct htable* ht, struct hnode* target, int (*hashfunc) (struct hnode*), int (*hnodecmp) (struct hnode*, struct hnode*));
int delete_hnode(struct htable* ht, struct hnode* target, int (*hashfunc) (struct hnode*), int (*hnodecmp) (struct hnode*, struct hnode*), void (*delete_handler) (struct hnode*));

int delete_hnode(struct htable* ht, struct hnode* target, int (*hashfunc) (struct hnode*), int (*hnodecmp) (struct hnode*, struct hnode*), void (*delete_handler) (struct hnode*))
{
    struct hnode *crnt, *temp;
    int found=0;
    
    for(crnt=ht->arr[hashfunc(target) % ht->size]; crnt != NULL; crnt = crnt->n)
    {
        if(crnt->n != NULL)
        {
            if(hnodecmp(target, crnt->n))
            {
                found=1;
                temp = crnt->n;
                crnt->n = crnt->n->n;
                delete_handler(temp);
                break;
            }
        }
    }
    return found;
}


struct hnode* lookup_hnode(struct htable* ht, struct hnode* target, int (*hashfunc) (struct hnode*), int (*hnodecmp) (struct hnode*, struct hnode*))
{
    struct hnode *crnt, *result=NULL;
    
    for(crnt=ht->arr[hashfunc(target) % ht->size]; crnt != NULL; crnt = crnt->n)
    {
        if(hnodecmp(crnt, target))
        {
            result = crnt;
            break;
        }
    }
    
    return result;
}

void print_htable(struct htable* h, void (*printfunc) (struct hnode*))
{
    int i;
    struct hnode* crnt;
    
    for(i=0;i<h->size;i++)
    {
        for(crnt= h->arr[i]; crnt != NULL; crnt = crnt->n)
        {
            printfunc(crnt);
        }
    }
}

struct htable* create_htable(int size)
{
    int i;
    struct htable *h = malloc(sizeof(struct htable));
    h->arr = malloc(sizeof(struct hnode)*size);
    
    for(i=0;i<size;i++)
        h->arr[i] = NULL;
    h->size = size;
    h->nelem=0;
        
    return h;
}

void delete_hnodechain(struct hnode* h)
{
    if(h->n != NULL)
        delete_hnodechain(h->n);
    free(h);
}

void delete_htable(struct htable* h)
{
    int i;
    for(i=0;i<h->size;i++)
        delete_hnodechain(h->arr[i]);
    free(h);
}

void insert_hnode(struct htable* ht, struct hnode* hn, int (*hashfunc) (struct hnode*))
{
    int dest = hashfunc(hn) % ht->size;
    struct hnode* temp = ht->arr[dest];
    ht->arr[dest] = hn;
    hn->n = temp;
}
