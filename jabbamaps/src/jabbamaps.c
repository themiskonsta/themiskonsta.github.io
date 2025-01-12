#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_CITIES 64

typedef struct
{
    char cities[100];
} 
cities;

int countcities(cities *x, int countcity, const char *city) 
{
    for (int i=0; i<countcity; i++) 
    {
        if (strcmp(x[i].cities, city) == 0) 
        {
            return i;
        }
    }
    return -1;
}

void nearest_city(int countCity, int *least_cost, int *best_road, int **distances)
{
    int *visited_cities = (int *)malloc(countCity*sizeof(int));
    int *road = (int *)malloc(countCity*sizeof(int));

    for (int j=0; j<countCity; j++)
    {
        visited_cities[j]=0;
    }

    int first_city=0;
    visited_cities[first_city] = 1;
    road[0] = first_city;
    int next_city;

    for(int y=1; y<countCity; y++)
    {
        int min_distance=INT_MAX;

        for (int z=0; z<countCity; z++)
        {
            if (!visited_cities[z] && distances[first_city][z] < min_distance) 
            {
                min_distance = distances[first_city][z];
                next_city = z;
            }
        }
        visited_cities[next_city]=1;
        road[y]=next_city;
        *least_cost+=min_distance;
        first_city=next_city;
    }

    memcpy(best_road, road, countCity * sizeof(int));

    free(visited_cities);
    free(road);
}

int main(int argc, char *argv[]) 
{
    if (argc<2)
    {
        printf("Usage: ./jabbamaps <filename>\n");
        return 1;
    }

    FILE *maps = fopen(argv[1], "r");
    
    if (!maps)
    {
        fprintf(stderr,"Error opening file\n");
        return 1;
    }


    cities *city = (cities*)malloc(MAX_CITIES*sizeof(cities));

    int **kilometres = (int**)malloc(MAX_CITIES*sizeof(int*));

    for (int i = 0; i < MAX_CITIES; i++) 
    {
        kilometres[i] = (int *)malloc(MAX_CITIES * sizeof(int));
    }

    char line[200];
    
    int distance;
    char city1[100], city2[100];
    int countCity=0;
    while (fgets(line, sizeof(line), maps)) 
    {
        if(sscanf(line, "%[^-]-%[^:]: %d", city1, city2, &distance)==3)
        {
            int find_city = countcities(city, countCity, city1);
            
            if(find_city==-1)
            {
                strncpy(city[countCity].cities, city1, sizeof(city[countCity].cities) - 1);
                city[countCity].cities[sizeof(city[countCity].cities) - 1] = '\0';
                find_city=countCity++;
            }

            int find_next_city= countcities(city,countCity,city2);

            if(find_next_city==-1)
            {
                strncpy(city[countCity].cities, city2, sizeof(city[countCity].cities) - 1);
                city[countCity].cities[sizeof(city[countCity].cities) - 1] = '\0';
                find_next_city=countCity++;
            }

            kilometres[find_city][find_next_city]=distance;
            kilometres[find_next_city][find_city]=distance;
        }
    }

    fclose(maps);

    int *best_road = (int *)malloc(countCity * sizeof(int));
    int least_cost = 0;

    nearest_city(countCity, &least_cost, best_road, kilometres);

    printf("We will visit the cities in the following order:\n"); 

    for (int i = 0; i < countCity - 1; i++) 
    {
        int current_city = best_road[i];
        int next_city = best_road[i + 1];
        
        printf("%s -(%d)->", city[current_city].cities, kilometres[current_city][next_city]);
    }

    printf("%s\n", city[best_road[countCity - 1]].cities);

    printf("Total cost: %d\n", least_cost);

    for (int i = 0; i < MAX_CITIES; i++) 
    {
        free(kilometres[i]);
    }

    free(city);
    free(best_road);

    return 0;
}



 













