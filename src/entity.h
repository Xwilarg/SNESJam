#pragma once

typedef struct
{
    int x;
    int y;
    int sprite;
} Entity;

void Entity_Init(Entity* entity, int sprite);
void Entity_Draw(Entity* entity);