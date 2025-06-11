#include "world.h"
#include "config.h"
#include "entity.h"

#define PLAYER_SPEED_GRASS 2
#define PLAYER_SPEED_ROAD 5

extern char patterns, patterns_end;
extern char palette;
extern char map, map_end;

static s16 playerX, playerY;
static Entity player;

static char debug_str[50];

static u8 player_speed = PLAYER_SPEED_ROAD;
static u8 collisions[WORLD_TILE_SIZE] =
{
    1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,3,3,3,1,1,1,1,1,1,1,0,0,0,
    1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,3,3,3,1,1,1,1,1,1,1,0,0,0,
    1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,3,3,3,1,1,1,1,1,1,0,0,0,0,
    1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,0,0,0,0,
    1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,0,0,0,0,
    1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,0,0,0,0,
    1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,0,0,0,1,
    1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,0,0,0,1,1,
    1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,0,0,0,1,1,
    1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,3,3,3,1,1,1,1,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,3,3,3,3,1,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,
    1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,1,0,0,0,0,0,0,0,0,0,0,
    1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,0,1,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1
};

// Take the player position and returns at which speed we are going
// If 0, it means that the tile is innaccessable
static u8 GetSpeed(s16 x, s16 y)
{
    u16 arrX = (u16)(x / TILE_SIZE);
    u16 arrY = (u16)(y / TILE_SIZE);

    u16 index = (arrY * WORLD_TILE_LENGTH) + arrX;

    u8 value = collisions[index];

    if (value == 0) return PLAYER_SPEED_ROAD;
    else if (value == 1) return PLAYER_SPEED_GRASS;

    return 0;
}

void World_Init(void)
{
    // Copy tiles to VRAMm
    bgInitTileSet(1, &patterns, &palette, 2, (&patterns_end - &patterns), 16 * 2, BG_16COLORS, 0x4000);

    // Copy Map to VRAM
    bgInitMapSet(1, &map, (&map_end - &map), SC_64x64, 0x1000);

    u16 startPos = WORLD_SIZE / 2;
    playerX = startPos;
    playerY = startPos;
    Entity_Init(&player, 0, startPos, startPos);
}

void World_SetScroll(bool forceRender)
{
    short pad0 = padsCurrent(0);

    bool didMove = false;

    // Get inputs
    if (pad0 & KEY_UP)
    {
        playerY -= player_speed;
        if (playerY < 0) playerY = 0;
        didMove = true;
    }
    if (pad0 & KEY_DOWN)
    {
        playerY += player_speed;
        if (playerY >= WORLD_SIZE) playerY = WORLD_SIZE - 1;
        didMove = true;
    }
    if (pad0 & KEY_RIGHT)
    {
        playerX += player_speed;
        if (playerX >= WORLD_SIZE) playerX = WORLD_SIZE - 1;
        didMove = true;
    }
    if (pad0 & KEY_LEFT)
    {
        playerX -= player_speed;
        if (playerX < 0) playerX = 0;
        didMove = true;
    }

    if (!didMove && !forceRender) return;

    s16 finalX = playerX - SCREEN_WIDTH_HALF;
    s16 finalY = playerY - SCREEN_HEIGHT_HALF;
    if (finalX < 0)
    {
        player.x = PLAYER_MID_X + finalX;
        finalX = 0;
    }
    else if (finalX > CANVAS_MAX_X)
    {
        player.x = PLAYER_MID_X + (finalX - CANVAS_MAX_X);
        finalX = CANVAS_MAX_X;
    }
    else player.x = PLAYER_MID_X;
    if (finalY < 0)
    {
        player.y = PLAYER_MID_Y + finalY;
        finalY = 0;
    }
    else if (finalY > CANVAS_MAX_Y)
    {
        player.y = PLAYER_MID_Y + (finalY - CANVAS_MAX_Y);
        finalY = CANVAS_MAX_Y;
    }
    else player.y = PLAYER_MID_Y;

    // Debug
    sprintf(debug_str, "Global: %u ; %u     ", playerX, playerY);
    consoleDrawText(10, 6, debug_str);
    sprintf(debug_str, "Local: %u ; %u     ", player.x, player.y);
    consoleDrawText(10, 8, debug_str);
    sprintf(debug_str, "Camera: %d ; %d     ", finalX, finalY);
    consoleDrawText(10, 10, debug_str);

    // Draw
    bgSetScroll(1, finalX, finalY);
    Entity_Draw(&player);
}