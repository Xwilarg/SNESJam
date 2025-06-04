#include "entity.h"

void Entity_Init(Entity* entity, int sprite)
{
    entity->x = 0;
    entity->y = 0;
    entity->sprite = sprite;
}

void Entity_Draw(Entity* entity)
{
}