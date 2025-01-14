#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_CITIES 64

typedef struct      //Define a structure to store the names of cities
{
    char cities[100];
} 
cities;

int countcities(cities *x, int countcity, const char *city)     //Function which finds the index of a city in the array
{
    for (int i=0; i<countcity; i++) 
    {
        if (strcmp(x[i].cities, city) == 0) 
        {
            return i;   //Return the index if the city is found
        }
    }
    return -1;
}

void nearest_city(int countCity, int *least_cost, int *best_road, int **distances)      //Function which finds the nearest city of the current city
{
    int *visited_cities = (int *)malloc(countCity*sizeof(int));      //Allocate memory to track visited cities and the road taken
    int *road = (int *)malloc(countCity*sizeof(int));

    for (int j=0; j<countCity; j++)     //All cities are unvisited in the beggining
    {
        visited_cities[j]=0;
    }

    int first_city=0;
    visited_cities[first_city] = 1;
    road[0] = first_city;

    for(int y=1; y<countCity; y++)      //Find all cities
    {
        int min_distance=INT_MAX;       //Initialize to a large value
        int next_city=0;

        for (int z=0; z<countCity; z++)     //Follow the shortest road for the next city
        {
            if (!visited_cities[z] && distances[first_city][z] < min_distance) 
            {
                min_distance = distances[first_city][z];
                next_city = z;
            }
        }
        visited_cities[next_city]=1;    //Mark the next city as visited and add it to the road 
        road[y]=next_city;
        *least_cost+=min_distance;      //Add the distance to the total cost
        first_city=next_city;
    }

    memcpy(best_road, road, countCity * sizeof(int));       //Copy the road to the best_road array

    free(visited_cities);
    free(road);
}

int main(int argc, char *argv[]) 
{
    if (argc<2)     //Check if arguments are more than 1
    {
        printf("Usage: ./jabbamaps <filename>\n");
        return 1;
    }

    FILE *maps = fopen(argv[1], "r");       //Open the file with the distances between the cities
    
    if (!maps)
    {
        fprintf(stderr,"Error opening file\n");
        return 1;
    }


    cities *city = (cities*)malloc(MAX_CITIES*sizeof(cities));       //Allocate memory for storing city names and kilometres

    int **kilometres = (int**)malloc(MAX_CITIES*sizeof(int*)); 

    for (int i = 0; i < MAX_CITIES; i++)        //Allocate memory for each row in the kilometres array 
    {
        kilometres[i] = (int *)malloc(MAX_CITIES * sizeof(int));
    }

    char line[200];
    
    int distance;
    char city1[100], city2[100];
    int countCity=0;
    while (fgets(line, sizeof(line), maps))     //Read the file line by line
    {
        if(sscanf(line, "%[^-]-%[^:]: %d", city1, city2, &distance)==3)     //Extract from every line the cities and the distance between them
        {
            int find_city = countcities(city, countCity, city1);
            
            if(find_city==-1)       // If city1 is not found, add it to the city array
            {
                strncpy(city[countCity].cities, city1, sizeof(city[countCity].cities) - 1);
                city[countCity].cities[sizeof(city[countCity].cities) - 1] = '\0';
                find_city=countCity++;
            }

            int find_next_city= countcities(city,countCity,city2);

            if(find_next_city==-1)      // If city2 is not found, add it to the city array
            {
                strncpy(city[countCity].cities, city2, sizeof(city[countCity].cities) - 1);
                city[countCity].cities[sizeof(city[countCity].cities) - 1] = '\0';
                find_next_city=countCity++;
            }

            kilometres[find_city][find_next_city]=distance;     // Update the kilometres array for the two cities
            kilometres[find_next_city][find_city]=distance;
        }
    }

    fclose(maps);       // Close the file

    int *best_road = (int *)malloc(countCity * sizeof(int));          // Allocate memory for storing the best road 
    int least_cost = 0;

    nearest_city(countCity, &least_cost, best_road, kilometres);       // Call the function nearest_city to find the nearest city and calculate the road and cost 

    printf("We will visit the cities in the following order:\n"); 

    for (int i = 0; i < countCity - 1; i++) 
    {
        int current_city = best_road[i];
        int next_city = best_road[i + 1];
        
        printf("%s -(%d)->", city[current_city].cities, kilometres[current_city][next_city]);       //Print the total road which include every city (except the last one) and the cost to go to the next city
    }

    printf("%s\n", city[best_road[countCity - 1]].cities);      //Print the last city

    printf("Total cost: %d\n", least_cost);     //Print the total cost

    for (int i = 0; i < MAX_CITIES; i++)        //Free memory which is dynamically allocated
    {
        free(kilometres[i]);
    }

    free(city);
    free(best_road);

    return 0;
}



 













