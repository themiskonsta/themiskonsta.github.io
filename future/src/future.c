#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double sma(double *array,double y,double x)     //Function which calculates the simple moving average
{
    double result=0;
    double sum=0;
    for(int i=y-x; i<=y; i++)       // Loop to calculate the sum of elements from (y - x) to y
    {
        sum+=array[i];      // Put all the values in the sum
    }
    result=sum/x;       // Calculate the sma, dividing the sum with the window size
    return result;
}

int main(int argc, char *argv[])
{   
    double x = (argc>3) ? atof(argv[3]): 50;    // Read the window size (default:50)
    double *array;
    double count=0;
    int i=0;
    double a;
    
    if (argc<2)     //Check if arguments are more than 1 
    {
        printf("Usage: ./future <filename> [--window N (default: 50)]\n");
        return 1;
    }
    
    FILE *numbers = fopen(argv[1], "r");    //Open the file for reading

    if (x<1)    //Check if window size is less than 1
    {
        printf("Window too small!\n");
        return 1;
    }
    
    if (!numbers)       //Check if the file is not opening
    {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    while (fscanf(numbers,"%lf", &a)==1)        //Count the numbers in the file 
    {
        count++;
    }

    rewind(numbers);        //Go to the beggining of the file 

    if (count<x)        //Compare the numbers in the file with the window size
    {
        printf("Window too large!\n");
        return 1;
    }

    array = (double*)malloc(count*sizeof(double));      //Store the numbers from the file in an array
    
    if (!array)         // Check if memory allocation fails
    {
        printf("Failed to allocate window memory\n");
        fclose(numbers);
        return 1;
    }

    while (fscanf(numbers,"%lf", &array[i])==1)     // Read the numbers from the file and store them in the array
    {
        i++;
    }
    fclose(numbers);        //Close the file

    printf("%lf\n",sma(array,count,x));     //Print the sma for the selected window

    free(array);        // Free the allocated memory from the array
    return 0;
}