#include "entity.h"
#include "config.h"

void Entity_Init(Entity* entity, u16 id, u16 startX, u16 startY)
{
    entity->id = id;
    entity->x = startX;
    entity->y = startY;
}

void Entity_Draw(Entity* entity)
{
    oamSet(entity->id, entity->x, entity->y, 3, 0, 0, 0, 0);
}