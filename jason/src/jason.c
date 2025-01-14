#include <stdio.h>
#include <string.h>
#include "neurolib.h"

int json_extension(const char*filename)     // Function to check if a file has a ".json" extension
{
    char*extension=".json";
    size_t x = strlen(filename);
    size_t y = strlen(extension);

    return (strcmp(filename + x - y, extension) == 0);      // Compare the last part of the filename with ".json"
}

int json_structure(const char*filename)     //Function to check if the structure of the file is correct
{
    FILE *file = fopen(filename, "r");      // Open the file
    
    if (file == NULL)       //Check if the file is empty
    {
        perror("file is empty\n");
        return 1; 
    }

    int first_count=fgetc(file);        // Read the first character of the file
    if (first_count!='{')
    {
        fprintf(stderr, "Not an accepted JSON!\n");
        return 1;
    }
    else
    {
        fseek(file,-1,SEEK_END);        // Move the file pointer to the last character
        int last_count=fgetc(file);     // Read the last character of the file
        
        if (last_count!='}')
        {
            fprintf(stderr, "Not an accepted JSON!\n");
            return 1;
        }
           
        fclose(file);       // Close the file 
        return 0;
    }
}

int main(int argc, char *argv[])
{
    if (argc<2)     //Check if arguments are more than 1
    {
        printf("Example: Usage: ./jason --extract json/1.json\n");
        return 1;
    }

    neurosym_init();

    if (strcmp(argv[1], "--extract")==0 && argv[2]!=NULL)       // Check if the second argument is '--extract' and a filename is provided
    {
        FILE *file=fopen(argv[2], "r");     // Open the file 
        
        if (file == NULL)       //Check if the file is empty
        {
            perror("file is empty\n");
            return 1;
        }

        if (json_extension(argv[2]))        // Check if the file has a .json extension
        {
            json_structure(argv[2]);        // Check if the structure of the file is correct
            
        
            int ch;
            char read[200];
            size_t i=0;
        
            while ((ch = fgetc(file)) != EOF)      // Read through the file character by character 
            {  
                if (ch == '[')      // Search for the beggining of a JSON array
                {
                    while ((ch = fgetc(file)) != EOF && ch != ']')      // Read characters until the end of the array
                    {
                        
                        if (i < sizeof(read) - 1)       //Store characters in the array
                        {  
                            read[i++] = ch; 
                        }
                    
                    }

                    read[i] = '\0';     //End of the string in the array

                    if (ch == ']')      // Search for the end of a JSON array
                    {
                        printf("%s\n", read);       // Print the content inside the array 
                    }
                }
       
            }
            fclose(file);       // Close the file 
            return 0;
        }

        else
        {
            printf("The file does not have the '.json' extension.\n");      // Case if the file does not have the '.json' extension
        }
    }
    return 0;
}