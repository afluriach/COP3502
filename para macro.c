#include <stdio.h>
#include <stdlib.h>

#define CUBE(x) (x*x*x)
#define MOD4(x) (x-(x/4)*4)
#define PRODLT100(x,y) ((x*y)<100?1:0)
#define MEMERROR {printf("error allocating memory\n"); system("PAUSE"); return 0;}

int intcmp(const void* x, const void* y)
{
    int *a= (int*)x;
    int *b=(int*)y;
    if(*a<*b)
        return -1;
    else if(*a==*b)
        return 0;
    else return 1;
}

void printhex(char* arr, int bytes)
{
    int i;
    for(i=0;i<bytes;i++)
        printf("%x ", arr[i]);
    printf("\n");
}

int xorarr(char* arr, int bytes, char key)
{
    int i;
    for(i=0;i<bytes;i++)
        arr[i] ^= key;
}

void scramble(char* arr, int bytes)
{
    int i;
    char temp;
    for(i=0;i<bytes;i++)
    {
        temp = arr[(2*i+1)%bytes];
        arr[(2*i+1)%bytes] = arr[i];
        arr[i] = temp;
    }
}   

void unscramble(char* arr, int bytes)
{
    int i;
    char temp;
    for(i=bytes-1;i>=0;i--)
    {
        temp = arr[(2*i+1)%bytes];
        arr[(2*i+1)%bytes] = arr[i];
        arr[i] = temp;
    }
}   
    
int main()
{
    
    int random_keys[10], i;
    srand(time(0));
    for(i=0;i<10;i++)
        random_keys[i] = rand();
    
    char s[] = ("hello world.\n");
    
    puts(s);
    for(i=0;i<sizeof(random_keys);i++)
    {
        scramble(s, sizeof(s));
        xorarr(s, sizeof(s), (char) random_keys[i]);
        puts(s);
        printhex(s, sizeof(s));
    }
    
    for(i=sizeof(random_keys)-1;i>=0;i--)
    {
        xorarr(s, sizeof(s), (char) random_keys[i]);
        unscramble(s, sizeof(s));
        puts(s);
        printhex(s, sizeof(s));
    }
    
    /*
    MEMERROR
    int i, arr[10];
    */
    /*
    int num1, num2;
    scanf("%d", &num1);
    printf("%d cubed is %d\n", num1, CUBE(num1));
    scanf("%d", &num1);
    printf("%d mod4 is %d\n", num1, MOD4(num1));
    scanf("%d %d", &num1, &num2);
    printf("product of %d and %d is %s\n", num1, num2, PRODLT100(num1, num2) ? "true" : "false");
    MEMERROR;
    */

/*    
    printf("Enter ten numbers\n");
    for(i=0;i<10;i++)
        scanf("%d", &(arr[i]));
        
    qsort(arr, 10, sizeof(int), intcmp);
    
    printf("Here is the array in sorted order.\n");
    for(i=0;i<10;i++)
        printf("%d ", arr[i]);
*/
    system("PAUSE");
    return 0;
}
