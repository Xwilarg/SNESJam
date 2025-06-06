#include "entity.h"

void Entity_Init(Entity* entity, int sprite, u16 startX, u16 startY)
{
    entity->x = startX;
    entity->y = startY;
    entity->sprite = sprite;
}

void Entity_Draw(Entity* entity)
{
    oamSet(0, 50, 50, 0, 0, 0, 0, 0); 
}