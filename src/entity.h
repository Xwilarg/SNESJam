#pragma once

#include <snes.h>

typedef struct
{
    u16 x;
    u16 y;
    int sprite;
} Entity;

void Entity_Init(Entity* entity, int sprite, u16 startX, u16 startY);
void Entity_Draw(Entity* entity);