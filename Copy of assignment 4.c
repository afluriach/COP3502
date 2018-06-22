//Antonio Fluriach
//COP 3302-0001, Summer 2010
//Assignment 4
//7-6-2010

#include <stdio.h>
#include <stdlib.h>

#define MAXAGE 100
#define NAMELEN 21 //number of bytes including the terminator
#define FILEPATHLEN 257 //number of bytes including the terminator
#define MEMERROR {printf("Error allocating memory. Program will now terminte.\n"); system("PAUSE"); exit(0);}

struct record
{
    char first[NAMELEN], last[NAMELEN];
    int age;
};

int cmprec(struct record* a, struct record* b);
void merge(struct record** s1, int s1size, struct record** s2, int s2size, struct record** dest);
void mergesort(struct record** recarr, int size);
void findrecord(struct record** recarr, int size);
void count_agefreq(struct record** recarr, int size);
void printlist(struct record** recarr, int size);
void count_agerange(struct record** recarr, int size);
void count_numages(struct record** recarr, int size);
void memcheck(void* p);

int main()
{
    //eof_check is not a boolean flag, it holds the return value of fscanf calls
    int i, numrecords, choice=0, eof_check;
    struct record** recarr;
    FILE* ifp;
    char ifpath[FILEPATHLEN], ch;
    
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
        {    printf("Error opening input file \"%s\"\n", ifpath);
            MEMERROR}
        else
            break;
    }
    
    //pointers to record structures will be stored in an array
    eof_check = fscanf(ifp, "%d", &numrecords);
    
    if(recarr<=0)
    {
        printf("Invalid number of records: %d. Program will now terminate.\n", numrecords);
        system("PAUSE");
        return 0;
    }
    
    recarr=malloc(sizeof(struct record*)*numrecords);
    memcheck(recarr);
    
    for(i=0;i<numrecords && eof_check != EOF;i++)
    {
        recarr[i] = malloc(sizeof(struct record));
        memcheck(recarr[i]);
        eof_check = fscanf(ifp, "%s%s%d", recarr[i]->first, recarr[i]->last, &(recarr[i]->age));
    }
    
    if(eof_check == EOF)
        printf("Warning, EOF reached prematurely.\n");
    
    mergesort(recarr, numrecords);
    
    while(1)
    {
        printf("0. Print list.\n"
               "1. Find record index by name and age.\n"
               "2. Count number of people in age range (inclusive).\n"
               "3. Count the number of unique age values.\n"
               "4. Count frequency of each age.\n"
               "5. exit\n"
               "> ");
        scanf("%d", &choice);
        if(choice==0)
            printlist(recarr, numrecords);
        else if(choice==1)
            findrecord(recarr, numrecords);
        else if(choice==2)
            count_agerange(recarr, numrecords);
        else if(choice==3)
            count_numages(recarr, numrecords);
        else if(choice==4)
            count_agefreq(recarr, numrecords);
        else if(choice==5)
            break;
        else
            printf("Invalid choice: %d.\n", choice);
        
        //clear stdin if user inputs something other than a single integer
        ch = getchar();
        while(ch != EOF && ch != '\n' && ch != '\r')
            ch = getchar();
    }
    
    for(i=0;i<numrecords;i++)
        free(recarr[i]);
    free(recarr);   
    fclose(ifp);
    system("PAUSE");
    return 0;
}

//prints out first index of record that matches search parameters, or a message
//if no such record is found
void findrecord(struct record** recarr, int size)
{
    char firstname[NAMELEN], lastname[NAMELEN];
    int i, age;
    printf("First name:\n");
    scanf("%s", firstname);
    printf("Last name:\n");
    scanf("%s", lastname);
    printf("Age: ");
    scanf("%d", &age);
    
    for(i=0;i<size;i++)
    {
        if(!strcmp(recarr[i]->first,firstname) && !strcmp(recarr[i]->last, lastname) && recarr[i]->age == age)
        {
            printf("%s %s (%d) is at pos %d.\n", firstname, lastname, age, i);
            return;
        }
    }       
    
    printf("%s %s (%d) not found.\n", firstname, lastname, age);
}

//counts the occurance of each age in the range 0 to MAXAGE inclusive, and
//prints out each nonzero age occurance 
void count_agefreq(struct record** recarr, int size)
{
    int i;
    int* agecounter = calloc(MAXAGE+1, sizeof(int));
    memcheck(agecounter);
    for(i=0;i<size;i++)
        //bounds check, make sure age value is a valid array index
        if(recarr[i]->age <= MAXAGE && recarr[i]->age >= 0)
            agecounter[recarr[i]->age]++;
    
    //column header
    printf("age\tfrequency\n");
    
    for(i=0;i<=MAXAGE;i++)
        if(agecounter[i])
            printf("%d\t%d people\n", i, agecounter[i]);
    free(agecounter);
}

//print every record in the list
void printlist(struct record** recarr, int size)
{
    int i;
    for(i=0;i<size;i++)
        printf("%d. %s %s %d\n", i, recarr[i]->first, recarr[i]->last, recarr[i]->age);
    printf("\n");
}

//returns 1 if the first argument is first or equal in sorted order, 0 if the second one is first in sorted order
int cmprec(struct record* a, struct record* b)
{
    //first by age
    if(a->age < b->age)
        return 1;
    else if(a->age > b->age)
        return 0;
    
    //then by last name
    if(strcmp(a->last, b->last) < 0)
        return 1;
    else if(strcmp(a->last, b->last) > 0)
        return 0;
        
    //then by first name
    if(strcmp(a->first, b->first) < 0)
        return 1;
    else if(strcmp(a->first, b->first) > 0)
        return 0;
    
    //at this point, both records contain identical information
    return 1;
}

//takes two arrays of record pointers and sorts them into a dest array    
void merge(struct record** s1, int s1size, struct record** s2, int s2size, struct record** dest)
{
    int i=0, j=0, k=0;

    while(i < s1size && j < s2size)
    {
        if(cmprec(s1[i], s2[j]))
            dest[k++] = s1[i++];
        else
            dest[k++] = s2[j++];
    }

    while(i<s1size)
        dest[k++] = s1[i++];
    
    while(j<s2size)
        dest[k++] = s2[j++];
}

//implements mergesort on an array of record pointers. 
void mergesort(struct record** recarr, int size)
{
    struct record **left, **right;
    int i;
    
    if(size <= 1)
        return;
    
    left = malloc(sizeof(struct record*)*size/2);
    memcheck(left);
    memcpy(left, recarr, (size/2)*sizeof(struct record*));
    
    right = malloc(sizeof(struct record*)*(size - size/2));
    memcheck(right);
    memcpy(right, recarr+(size/2), (size - size/2)*sizeof(struct record*));
    
    mergesort(left, size/2);
    mergesort(right, size-size/2);

    merge(left, size/2, right, size-size/2, recarr);
    free(left);
    free(right);
}

//counts the number of ages in a given range, inclusive
void count_agerange(struct record** recarr, int size)
{
    int min, max, i, count=0;
    printf("Minimum:\n");
    scanf("%d", &min);
    printf("Maximum:\n");
    scanf("%d", &max);
    if(min<0)
    {
        printf("Invalid minimim value. Using value 0 for minimum.\n");
        min=0;
    }
    if(max>MAXAGE)
    {
        printf("Invalid maximum value. Using value %d for maximum.\n", MAXAGE);
        max = MAXAGE;
    }
    for(i=0;i<size;i++)
        if(recarr[i]->age >= min && recarr[i]->age <= max)
            count++;
    printf("There are %d people in the range %d to %d.\n", count, min, max);
}

//counts and prints out the number of unique ages in records in recarr
void count_numages(struct record** recarr, int size)
{
    int i, count=0, *agearr = calloc(MAXAGE+1, sizeof(int));
    memcheck(agearr);
    for(i=0;i<size;i++)
        //bounds check before trying to access given array index
        if(recarr[i]->age <= MAXAGE && recarr[i]->age >= 0)
            agearr[recarr[i]->age]++;
    for(i=0;i<=MAXAGE;i++)
        if(agearr[i])
            count++;
    printf("There are %d unique age values in the list.\n", count);
    free(agearr);
}

//For dynamically allocated memory. Gives a warning and terminates the program
//if it gets a NULL pointer
void memcheck(void* p)
{
    if(p==NULL)
    {
        printf("Error allocating memory. Program will now terminte.\n");
        system("PAUSE");
        exit(0);
    }
}
