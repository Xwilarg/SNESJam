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
    oamSet(entity->id, PLAYER_MID_X, PLAYER_MID_Y, 3, 0, 0, 0, 0);
}