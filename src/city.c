#include <stdlib.h>
#include <string.h>

#include "utils.h"

#include "city.h"

City* City_Init(char* name, u16 x, u16 y)
{
    City* city = malloc(sizeof(City));

    char* welcomeSentence = "Welcome in ";

    city->welcomeText = malloc(strlen(welcomeSentence) + strlen(name) + 1);

    strcpy(city->welcomeText, welcomeSentence);
    strcat(city->welcomeText, name);

    city->x = x;
    city->y = y;

    city->availablePackages = 0;

    return city;
}

void City_Free(City* city)
{
    free(city->welcomeText);
    free(city);
}