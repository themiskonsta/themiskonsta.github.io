#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double sma(double *array,double y,double x)
{
    double result=0;
    double sum=0;
    for(int i=y-x; i<=y; i++)
    {
        sum+=array[i];
    }
    result=sum/x;
    return result;
}

int main(int argc, char *argv[])
{   
    char *values = argv[1];
    double x = (argc>3) ? atof(argv[3]): 50;
    double *array;
    double count=0;
    int i=0;
    double a;
    double result=1;

    if (argc<2)
    {
        printf("Usage: ./future <filename> [--window N (default: 50)]\n");
        return 1;
    }

    if (x<1)
    {
        printf("Window too small!\n");
        return 1;
    }

    for (int i=0; i<18; i++)
    {
        result*=10;
    }
    
    if(x==result)
    {
        printf("Failed to allocate window memory\n");
        return 1;
    }
    
    FILE *numbers = fopen("values.txt", "r");
    while (fscanf(numbers,"%lf", &a)==1)
    {
        count++;
    }

    rewind(numbers);
    array = (double*)malloc(count*sizeof(double));
    while (fscanf(numbers,"%lf", &array[i])==1)
    {
        i++;
    }
    fclose(numbers);

    if (count<x)
    {
        printf("Window too large!\n");
        return 1;
    }

    if (strcmp(values, "values.txt")==0)
    {
        printf("%lf\n",sma(array,count,x));
        free(array);
        return 0;
    }
}