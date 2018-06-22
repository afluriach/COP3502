//Antonio Fluriach
//6-27-2010
//COP 3502-0001
//Assignment 3

#include <stdio.h>
#define STACK_SIZE 1000
#define QUEUE_SIZE 1000
#define FILEPATHLEN 256

struct stack
{
    //top: the topmost item on the stack, empty stack if < 0
    int *arr, size, top;
};

struct queue
{
    //size = number of items in the array
    //front=first position in the queue
    //end = first availible pos in the queue
    //number[i] = employee number for employee in pos i
    //state[i] = employee state for employee in pos i; 0= waiting to pick up a
    //tray, 1=waiting to drop one off
    //tray[i]= tray number that employee is holding for employee in pos i, -1
    //if employee doesn't have a tray yet
    
    int size, front, end;
    int *number, *state, *tray;
};

struct stack* create_stack(int size);
void destroy_stack(struct stack* s);
void push(struct stack* s, int num);
int stack_peek(struct stack* s);
int pop(struct stack* s);
int stack_isempty(struct stack* s);
struct queue* create_queue(int size);
void destroy_queue(struct queue* q);
void enqueue(struct queue* q, int number, int state, int tray);
void dequeue(struct queue* q, int *number, int *state, int *tray);
int queue_isempty(struct queue* q);
void enqueue_employees(struct queue* line, int minute, FILE* ifp, FILE* ofp);
void push_trays(struct stack* traystack, int minute, FILE* ifp, FILE* ofp);
void dequeue_employee(struct queue* line, struct stack* traystack, int minute, FILE* ifp, FILE* ofp);

int main()
{
    FILE *ifp, *ofp;
    char ifpath[FILEPATHLEN], ofpath[FILEPATHLEN], op, *temp;
    int i, j, numlines, minute=1;
    
    while (1)
    {    
        printf("Input file path, or type \"exit\" to quit: ");
        gets(ifpath);
        if(!strcmp(ifpath, "exit"))
        {
            printf("Goodbye.\n");
            system("PAUSE");
            return 0;
        }
        ifp = fopen(ifpath, "r");
        if(ifp == NULL)
            printf("Error opening input file \"%s\"\n", ifpath);
        else
            break;
    }
    
    while (1)
    {    
        printf("Output file path, or type \"exit\" to quit: ");
        gets(ofpath);
        if(!strcmp(ofpath, "exit"))
        {
            printf("Goodbye.\n");
            system("PAUSE");
            exit(0);
        }
        ofp = fopen(ofpath, "w");
        if(ofp == NULL)
            printf("Error opening output file \"%s\"\n", ofpath);
        else
            break;
    }
    
    struct queue* line = create_queue(QUEUE_SIZE);
    struct stack* traystack = create_stack(STACK_SIZE);
    
    fscanf(ifp, "%d", &numlines);
    
    for(i=0;i<numlines; i++, minute++)
    {
        fscanf(ifp, " %c", &op);
        if(op=='E' || op=='e')
            enqueue_employees(line, minute, ifp, ofp);
        else if(op=='T' || op=='t')
            push_trays(traystack, minute, ifp, ofp);
        else if(op=='D' || op=='d')
            dequeue_employee(line, traystack, minute, ifp, ofp);        
    }
    //continue dequeue operation until queue is empty
    while(!queue_isempty(line))
    {
        dequeue_employee(line, traystack, minute, ifp, ofp);
        minute++;
    }
    
    fprintf(ofp, "Minute %d. Lunchtime complete! Long live our fearless leader!\n", minute);
    
    fclose(ifp);
    fclose(ofp);
    destroy_stack(traystack);
    destroy_queue(line);
    return 0;
}

//create stack, initialize variables, allocate memory for the arr in the stack, and return a pointer
struct stack* create_stack(int size)
{
    struct stack* s = malloc(sizeof(struct stack));
    s->size = size;
    s->arr = malloc(sizeof(int)*s->size);
    s->top = -1;
    return s;
}

void destroy_stack(struct stack* s)
{
    free(s->arr);
    free(s);
}

//if not full, increment top and push num into the new topmost pos on the stack
void push(struct stack* s, int num)
{
    if(s->top >= s->size - 1)
        return;
    else
        s->top++;
    s->arr[s->top] = num;
}

//see the topmost item without popping it
int stack_peek(struct stack* s)
{
    return s->arr[s->top];
}

//returns -1 if stack is empty, otherwise pop a number from the stack
int pop(struct stack* s)
{
    if(stack_isempty(s))
        return -1;
    else
    {
        return s->arr[s->top--];
    }
}

//return true if stack is empty, false otherwise
int stack_isempty(struct stack* s)
{
    return (s->top < 0);
}

//creates a queue, allocates memory for the three arrays in the queue that
//represent the employee's number, state, and tray that he is holding for
//each position in the q
struct queue* create_queue(int size)
{
    int i;
    struct queue* q = malloc(sizeof(struct queue));
    q->size = size;
    q->number = malloc(sizeof(int) * q->size);
    q->state = malloc(sizeof(int) * q->size);
    q->tray = malloc(sizeof(int) * q->size);
    q->front=0;
    q->end=0;
    return q;
}    

void destroy_queue(struct queue* q)
{
    free(q->number);
    free(q->state);
    free(q->tray);
    free(q);
}

void enqueue(struct queue* q, int number, int state, int tray)
{
    q->number[q->end] = number;
    q->state[q->end] = state;
    q->tray[q->end] = tray;
    q->end = (q->end+1) % q->size;
}

void dequeue(struct queue* q, int *number, int *state, int *tray)
{
    int temp = q->front;
    if(queue_isempty(q))
        return;
    else
    {
        q->front = (q->front + 1) % q->size;
        *number = q->number[temp];
        *state = q->state[temp];
        *tray = q->tray[temp];
    }
}

int queue_isempty(struct queue* q)
{
    return (q->front == q->end);
}

void enqueue_employees(struct queue* line, int minute, FILE* ifp, FILE* ofp)
{
    int num_employees, number, i;
    fscanf(ifp, "%d", &num_employees);
    fprintf(ofp, "Minute %d, %d people entered the line\n", minute, num_employees);
    
    for(i=0;i<num_employees;i++)
    {
        fscanf(ifp, " %d", &number);
        enqueue(line, number, 0, -1);
    }
}
void push_trays(struct stack* traystack, int minute, FILE* ifp, FILE* ofp)
{
    int num_trays, i, temp;
    fscanf(ifp, " %d", &num_trays);
    
    for(i=0;i<num_trays;i++)
    {
        fscanf(ifp, "%d", &temp);
        push(traystack, temp);
    }
    fprintf(ofp, "Minute %d: %d trays added to the dispenser. The topmost tray"
            " is %d.\n", minute, num_trays, stack_peek(traystack));
}

void dequeue_employee(struct queue* line, struct stack* traystack, int minute, FILE* ifp, FILE* ofp)
{   
    int number, state, tray;
    if(!queue_isempty(line))
        dequeue(line, &number, &state, &tray);
    else 
        return;
    
    //if state==0, employee will pick up a tray
    if(state == 0)
    {
        if(!stack_isempty(traystack))
        {
            tray = pop(traystack);
            fprintf(ofp, "Minute %d: Employee %d took tray %d from dispenser.\n", minute, number, tray);
            enqueue(line, number, 1, tray);
        }
        else
        {
            fprintf(ofp, "Minute %d: The dispenser is empty! Such incompetence must be punished!", minute);
            fclose(ifp);
            fclose(ofp);
            destroy_stack(traystack);
            destroy_queue(line);
            exit(0);
        }
    }
    //the employee will drop off a tray
    else
    {
        push(traystack, tray);
        fprintf(ofp, "Minute %d: Employee %d returned tray %d to the dispenser.\n",
                minute, number, tray);
    }
}
