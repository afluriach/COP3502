//Antonio Fluriach
//COP3502-C001
//05-28-2010
//Assignment 1: Linked Lists

#include <stdio.h>
#define MAXLEN 21 //total number of bytes reserved for each string

struct node
{
    char firstname[MAXLEN], lastname[MAXLEN];
    int mana;
    struct node* next;
};

//new_orb, delete_by_name, and delete_by_index pass a poniter to the head
//pointer so it can be changed.
void new_orb(struct node** head);
void delete_by_name(struct node** head);
void delete_by_index(struct node** head);
void print_thread(struct node* head);
int compute_capacity(struct node* head);
void delete_list(struct node* head);

int main()
{
    int op;
    struct node* head=NULL;
    while(1)
    {
        printf("Enter a numerical command:\n"
               "1. Read in Orb\n"
               "2. Delete Orb by name\n"
               "3. Delete Orb by position\n"
               "4. Print Thread\n"
               "5. Calculate Daemon Capaticty\n"
               "6. Quit\n");
        scanf("%d", &op);
        if(op==1)
            new_orb(&head);
        else if(op==2)
            delete_by_name(&head);
        else if(op==3)
            delete_by_index(&head);
        else if(op==4)
            print_thread(head);
        else if(op==5)
            printf("The current Daemon capacity is %d.\n",
             compute_capacity(head));
        else if(op==6)
            break;
        else
            printf("Invalid command\n");
    }
    delete_list(head);
    system("PAUSE");
    return 0;
}

//takes in a head pointer by reference; creates a new node, populates it
//and inserts it into the list
void new_orb(struct node** head)
{
    int i, pos;
    struct node* newnode = malloc(sizeof(struct node));
    struct node* tr;
    newnode->next = NULL;
    
    printf("First name:\n");
    scanf("%s", newnode->firstname);
    printf("Last name: ");
    scanf("%s", newnode->lastname);
    printf("Mana content: ");
    scanf("%d", &newnode->mana);
    printf("Position to insert at: ");
    scanf("%d", &pos);
    
    //special case: insert at beginning; either way, it will be inserted at
    //position 0.
    if(pos==0 || *head==NULL)
    {
        //same outcome, just different messages
        if(pos==0)
            printf("Inserting at location 0.\n");
        else if(*head==NULL)
            printf("Emtpy list, inserting at location 0.\n");
        newnode->next = *head;
        *head = newnode;
    }
    else
    {
        //walk through the list until you reach pos-1 or the last node in the
        //list
        for(i=0, tr=*head; i<pos-1, tr->next != NULL; i++, tr=tr->next) //stop at the one previous
            ;
        //if it stopped prematurely, print the actual location
        if(i<pos-1)
            printf("Cannot insert at location %d. Inserting at location %d.\n",
             pos, i);
        newnode->next = tr->next;
        tr->next = newnode;
    }
}

//accepts a head pointer by reference; takes in the first and last name and
//deletes the first node whose first and last name match exactly; prints a
//message for either success or failure
void delete_by_name(struct node** head)
{
    struct node *tr, *temp;
    int found=0;
    char firstname[MAXLEN], lastname[MAXLEN];
    
    printf("First name: ");
    scanf("%s", firstname);
    printf("Last name: ");
    scanf("%s", lastname);
    
    // first check to see if the head node is the match
    if(strcmp(firstname,(*head)->firstname)==0 && 
       strcmp(lastname,(*head)->lastname)==0)
    {
        found=1;
        temp = (*head)->next;
        free(*head);
        *head=temp;
    }      
    
    //otherwise, walk through the list
    else for(tr=*head; tr!= NULL; tr->next)
    {
        if(strcmp(firstname,tr->next->firstname)==0 && 
           strcmp(lastname,tr->next->lastname)==0)
        {
            found=1;
            temp = tr->next->next;
            free(tr->next);
            tr->next = temp;
            break;
        }
    }
    if(found)
        printf("%s %s baleeted.\n", firstname, lastname);
    else
        printf("%s %s was not found in the Thread.\n", firstname, lastname);
}

//takes in a head pointer by reference; accepts an integer from the user and
//deletes the node at that position if it is a valid index.
void delete_by_index(struct node** head)
{
    int index, i;
    struct node* temp;
    struct node* tr;
    printf("Index of orb to be deleted:\n");
    scanf("%d", &index);
    
    //special case: deleting the head node
    if(index==0)
    {
        if(*head==NULL)
            printf("Not a valid index.\n");
        else
        {
            printf("%s %s deleted.\n", (*head)->firstname, (*head)->lastname);
            temp = (*head)->next;
            free(*head);
            *head = temp;
        }
    }
    else
    {
        tr=*head;
        for(i=0; i<index;i++)
        {
            if(tr->next != NULL)
                tr = tr->next;
            else
            {
                printf("Not a valid index.\n");
                return;
            }
        }
        //tr should now be at element index-1; the next one will be
        //deleted if next is not NULL
        if(tr->next != NULL)
        {
            printf("%s %s deleted.\n", tr->next->firstname,tr->next->lastname);
            temp = tr->next->next;
            free(tr->next);
            tr->next = temp;
        }
        else
        {
            printf("Not a valid index.\n");
        }
    }
}

//takes in a head pointer and prints all the Orbs
void print_thread(struct node* head)
{
    printf("The Thread contains:\n");
    struct node* tr;
    for(tr=head; tr!=NULL;tr=tr->next)
        printf("%s %s, %d\n", tr->firstname, tr->lastname, tr->mana);
}

//takes in a head pointer, sums odd and even mana values, and returns the
//Daemon capacity
int compute_capacity(struct node* head)
{
    struct node* tr;
    int i, sumodd=0, sumeven=0;
    for(i=0, tr=head; tr!=NULL; tr=tr->next, i++)
    {
        if(i%2==0)
            sumeven += tr->mana;
        else
            sumodd += tr->mana;
    }
    return sumodd*sumeven;
}

//takes in a head pointer; walks through the list and frees the memory for each
//node
void delete_list(struct node* head)
{
    if(head==NULL)
        return;
    struct node *tr, *temp;
    for(tr=head;tr != NULL; tr->next)
    {
        temp = tr->next;
        free(tr);
        tr=temp;
    }
}
