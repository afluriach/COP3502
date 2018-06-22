#include <stdio.h>
#define SQRT_MARGIN 0.001

double harmonic(int n);
double dabs(double n);
double square_root(double n);
double sqrt_rec(double min, double max, double n);
void ndigitnum(int digits_to_print, int digits_in_list, int* list);
void digits_rec(int digits_to_print, int digits_in_list, int* list, int* combination, int index);

/*
void int_to_digits(int num, int digit_array, int max_digits)
{
    int i;
    for(i=max_digits;num>0 && i < max_digits)
    {
        digit_array[i] = num % 10;
        num /= 10;
    }
    */
    
    
int main()
{
    int digits[] = {1,3,5,7,9};
    ndigitnum(2, 5, digits);
    system("PAUSE");
    return 0;
}

double harmonic(int n)
{
    if(n==1)
        return 1;
    else
        return (1.0/n) + harmonic(n-1);
}

double dabs(double n)
{
    if(n<0)
        return n*-1;
    else
        return n;
}

double square_root(double n)
{
    return sqrt_rec(1,n,n);
}

double sqrt_rec(double min, double max, double n)
{
    double mid = (min+max)/2;
    //square root is less than midpoint
    if(dabs(mid*mid-n) < SQRT_MARGIN)
        return mid;
    if(mid*mid>n)
        return sqrt_rec(min,mid,n);
    else
        return sqrt_rec(mid,max,n);
}

void ndigitnum(int digits_to_print, int digits_in_list, int* list)
{
    int *combination = malloc(sizeof(int)*digits_to_print);
    digits_rec(digits_to_print, digits_in_list, list, combination, 0);
}   

void digits_rec(int digits_to_print, int digits_in_list, int* list, int* combination, int index)
{
    int i;
    if (digits_to_print > 0)
    {
        for(i=0; i<digits_in_list; i++)
        {
            printf("%d", combination[index]);
            digits_rec(digits_to_print-1,digits_in_list,list, combination, index+1);
        }
    }
    else
    {
        for(i=0;i<digits_to_print;i++)
        {
            printf("%d", combination[i]);
        }
        printf(" ");
    }
}
