#include "world.h"
#include "config.h"

extern char patterns, patterns_end;
extern char palette;
extern char map, map_end;

void World_Init(void)
{
    // Copy tiles to VRAMm
    bgInitTileSet(1, &patterns, &palette, 2, (&patterns_end - &patterns), 16 * 2, BG_16COLORS, 0x4000);

    // Copy Map to VRAM
    bgInitMapSet(1, &map, (&map_end - &map), SC_64x64, 0x1000);
}

void World_SetScroll(u16 x, u16 y)
{
    u16 finalX = x - SCREEN_WIDTH_HALF;
    u16 finalY = y - SCREEN_HEIGHT_HALF;
    if (finalX < 0) finalX = 0;
    else if (finalX > CANVAS_MAX_X) finalX = CANVAS_MAX_X;
    if (finalY < 0) finalX = 0;
    else if (finalY > CANVAS_MAX_Y) finalX = CANVAS_MAX_Y;
    bgSetScroll(1, finalX, finalY);
}