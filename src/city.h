#pragma once

#include <snes.h>

typedef struct
{
    char* welcomeText;
    char* name;
    u16 x;
    u16 y;
    u8 availablePackages;
} City;

City* City_Init(char* name, u16 x, u16 y);
void City_Free(City* city);