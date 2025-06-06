#pragma once

#include <snes.h>

typedef struct
{
    u16 id;
    u16 x;
    u16 y;
} Entity;

void Entity_Init(Entity* entity, u16 id, u16 startX, u16 startY);
void Entity_Draw(Entity* entity);