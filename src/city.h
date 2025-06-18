#pragma once

#include <snes.h>

typedef struct
{
    char* welcomeText;
    u8 x;
    u8 y;
} City;

City* City_Init(char* name, u8 x, u8 y);
void City_Free(City* city);