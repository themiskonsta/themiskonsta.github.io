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
    double x = (argc>3) ? atof(argv[3]): 50;
    double *array;
    double count=0;
    int i=0;
    double a;
    
    if (argc<2)
    {
        printf("Usage: ./future <filename> [--window N (default: 50)]\n");
        return 1;
    }

    if (x=0)
    {
        printf("Window too small!\n");
        return 1;
    }
    
    FILE *numbers = fopen(argv[1], "r");

    if (!numbers) 
    {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    while (fscanf(numbers,"%lf", &a)==1)
    {
        count++;
    }

    rewind(numbers);
    
    if (count<x)
    {
        printf("Window too large!\n");
        return 1;
    }

    array = (double*)malloc(count*sizeof(double));
    
    if (!array) 
    {
        printf("Memory allocation failed!\n");
        fclose(numbers);
        return 1;
    }

    while (fscanf(numbers,"%lf", &array[i])==1)
    {
        i++;
    }
    fclose(numbers);

    printf("%lf\n",sma(array,count,x));

    free(array);
    return 0;
}