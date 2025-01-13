#include <stdio.h>
#include <string.h>
#include "neurolib.h"

int json_extension(const char*filename)
{
    char*extension=".json";
    size_t x = strlen(filename);
    size_t y = strlen(extension);

    return (strcmp(filename + x - y, extension) == 0);
}

int json_structure(const char*filename)
{
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) 
    {
        perror("Error opening file\n");
        return 1; 
    }

    int first_count=fgetc(file);
    if (first_count!='{')
    {
        fprintf(stderr, "Not an accepted JSON!\n");
        return 1;
    }
    else
    {
        fseek(file,-1,SEEK_END);
        int last_count=fgetc(file);
        
        if (last_count!='}')
        {
            fprintf(stderr, "Not an accepted JSON!\n");
            return 1;
        }
           
        fclose(file);
        return 0;
    }
}

int main(int argc, char *argv[])
{
    if (argc<2)
    {
        printf("Example: Usage: ./jason --extract json/1.json\n");
        return 1;
    }

    neurosym_init();

    if (strcmp(argv[1], "--extract")==0 && argv[2]!=NULL)
    {
        FILE *file=fopen(argv[2], "r");
        
        if (file == NULL) 
        {
            perror("file is empty\n");
            return 1;
        }

        if (json_extension(argv[2]))
        {
            json_structure(argv[2]);
            
        
            int ch;
            char read[200];
            size_t i=0;
        
            while ((ch = fgetc(file)) != EOF) 
            {  
                if (ch == '[') 
                {
                    while ((ch = fgetc(file)) != EOF && ch != ']') 
                    {
                        
                        if (i < sizeof(read) - 1) 
                        {  
                            read[i++] = ch; 
                        }
                    
                    }

                    read[i] = '\0';

                    if (ch == ']') 
                    {
                        printf("%s\n", read);
                    }
                }
       
            }
            fclose(file);
            return 0;
        }

        else
        {
            printf("The file does not have the '.json' extension.\n");
        }
    }
    return 0;
}