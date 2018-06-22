#include <stdio.h>
#include <math.h>


int main()
{

int i, sum=0;

for(i=3;i<=20;i++)
{
    sum+= (4*pow(2,i));
}

printf("%d", sum);
system("PAUSE");
}
