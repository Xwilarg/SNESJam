#include <stdlib.h>

#include "world.h"
#include "config.h"
#include "entity.h"
#include "city.h"
#include "package.h"

#define PLAYER_SPEED_TREE 1
#define PLAYER_SPEED_GRASS 2
#define PLAYER_SPEED_ROAD 5

#define CITY_COUNT 5

extern char patterns, patterns_end;
extern char palette;
extern char map, map_end;

static s16 playerX, playerY;
static Entity player;

static char debug_str[50];

static City** cities;

static u8 player_speed = PLAYER_SPEED_ROAD;
static u8 collisions[WORLD_TILE_SIZE] =
{
    1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,3,3,3,1,1,6,6,1,1,1,0,0,0,
    1,1,1,1,1,6,6,1,0,0,4,0,1,1,1,1,1,1,1,3,3,3,1,1,6,6,1,1,1,0,4,0,
    1,1,1,1,1,6,6,1,0,0,0,0,1,1,1,1,1,1,1,3,3,3,1,6,6,6,1,1,0,0,0,0,
    1,1,1,1,6,6,6,1,0,0,0,1,1,6,1,1,1,1,3,3,3,3,1,6,6,6,1,1,0,0,0,0,
    1,1,1,1,6,6,6,1,0,0,0,1,6,6,6,1,1,1,3,3,3,3,1,6,6,6,1,1,0,0,0,0,
    1,1,1,6,6,6,1,1,0,0,0,1,6,6,6,6,1,1,3,3,3,3,1,6,6,1,1,1,0,0,0,0,
    1,6,6,6,6,1,1,1,0,0,0,6,6,6,6,6,1,1,3,3,3,3,1,6,6,1,1,1,0,0,0,1,
    1,6,6,6,6,1,1,0,0,0,0,6,6,6,6,6,1,1,3,3,3,3,1,6,6,1,1,0,0,0,1,1,
    6,6,6,6,1,1,1,0,0,0,0,6,6,6,6,6,1,1,3,3,3,3,1,1,1,1,1,0,0,0,1,1,
    6,6,1,1,1,1,1,0,0,0,0,1,6,6,6,6,1,1,3,3,3,1,1,1,1,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,0,0,0,0,1,6,6,6,1,1,3,3,3,3,1,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,
    0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,0,0,0,0,4,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,
    1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,1,0,0,0,0,0,0,0,0,0,0,
    6,6,1,1,1,0,0,0,1,1,1,0,0,0,0,0,1,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,
    6,6,6,1,1,0,0,0,1,1,1,6,6,6,1,1,1,3,3,3,3,1,1,1,6,6,6,1,1,1,1,1,
    6,6,6,1,1,0,0,0,1,6,6,6,6,6,6,6,1,3,3,3,3,1,1,6,6,6,6,6,6,1,1,1,
    6,6,6,1,0,0,0,0,1,1,6,6,6,6,6,1,1,3,3,3,3,1,1,6,1,6,6,6,6,6,1,1,
    6,6,1,1,0,0,0,0,1,1,6,6,6,6,6,1,3,3,3,3,1,1,1,6,6,6,6,6,6,6,1,1,
    6,6,1,1,0,0,0,0,1,1,6,6,6,6,6,1,3,3,3,3,1,1,1,6,6,6,6,6,6,6,1,1,
    6,6,1,1,0,0,0,0,1,1,1,6,6,6,6,1,3,3,3,3,1,1,1,6,6,6,6,6,6,6,6,1,
    1,1,1,0,0,0,0,0,1,1,1,6,6,6,1,1,3,3,3,3,1,1,1,1,6,6,6,6,6,6,6,1,
    1,1,1,0,0,0,0,1,1,1,1,6,6,6,1,1,3,3,3,3,1,1,1,1,6,6,6,6,6,6,6,1,
    1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,6,6,6,6,6,6,6,1,
    1,1,1,0,0,0,0,1,1,1,1,6,1,1,1,1,3,3,3,1,1,1,1,1,1,6,6,6,6,6,6,1,
    6,6,1,0,0,0,1,1,1,1,6,6,1,1,1,1,3,3,3,1,1,1,1,1,1,1,6,6,6,6,1,1,
    6,6,1,0,0,0,1,1,1,6,6,6,1,1,1,1,3,3,3,1,1,1,1,6,6,1,1,6,6,1,1,1,
    6,6,1,0,0,0,1,1,1,6,6,6,6,1,1,1,3,3,3,1,1,1,6,6,6,1,1,1,1,1,1,1,
    1,1,1,0,0,0,1,1,1,6,6,6,6,1,1,1,3,3,3,1,1,1,6,6,6,6,1,1,1,1,1,1,
    1,1,0,0,4,0,1,1,1,6,6,6,6,1,1,3,3,3,3,1,1,1,6,6,6,6,6,1,1,1,1,1,
    1,1,0,0,0,0,1,1,1,6,6,6,6,1,1,3,3,3,3,1,1,1,6,6,6,6,6,1,1,1,1,1
};

// MENU

static u8 currentCity;
static u8 menuIndex;
static short lastPad0;

static Package* currentPackage;

// Take the player position and returns at which speed we are going
// If 0, it means that the tile is innaccessable
static u8 GetSpeed(u16 arrX, u16 arrY)
{
    u16 index = (arrY * WORLD_TILE_LENGTH) + arrX;

    u8 value = collisions[index];

    if (value == 0) return PLAYER_SPEED_ROAD;
    else if (value == 1) return PLAYER_SPEED_GRASS;
    else if (value == 6) return PLAYER_SPEED_TREE;
    else if (value == 4) return U8_MAX;

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

    cities = malloc(sizeof(City*) * 6);

    cities[0] = City_Init("Aenra", 1, 12);
    cities[1] = City_Init("Bear", 10, 1);
    cities[2] = City_Init("Soorn", 4, 30);
    cities[3] = City_Init("Dekrak", 30, 1);
    cities[4] = City_Init("Trek Vaek", 30, 12);
    cities[5] = NULL;

    currentCity = U8_MAX;
    lastPad0 = 0;
    currentPackage = NULL;
}

static void ClearMenuUI()
{
    sprintf(debug_str, "                                 ");
    consoleDrawText(10, 20, debug_str);
    sprintf(debug_str, "                                 ");
    consoleDrawText(10, 22, debug_str);
    sprintf(debug_str, "                                 ");
    consoleDrawText(10, 24, debug_str);
    sprintf(debug_str, "                                 "); // City name
    consoleDrawText(10, 6, debug_str);
}

static bool canGetPackage = true;
static bool canDeliverPackage = true;
static void RenderMenu()
{
    short pad0 = padsCurrent(0);
    if ((pad0 & KEY_DOWN) && (lastPad0 & KEY_DOWN) == 0)
    {
        if (menuIndex == 2) menuIndex = 0;
        else menuIndex++;
    }
    else if ((pad0 & KEY_UP) && (lastPad0 & KEY_UP) == 0)
    {
        if (menuIndex == 0) menuIndex = 2;
        else menuIndex--;
    }
    else if ((pad0 & KEY_A) && (lastPad0 & KEY_A) == 0)
    {
        if (menuIndex == 0 && canGetPackage)
        {
            currentPackage = malloc(sizeof(Package));
            currentPackage->from = currentCity;
            currentPackage->to = (playerX * playerY) % CITY_COUNT;
            ClearMenuUI();
        }
        else if (menuIndex == 1 && canDeliverPackage)
        {

        }
        else if (menuIndex == 2)
        {
            ClearMenuUI();
            currentCity = U8_MAX;
            return;
        }
    }
    lastPad0 = pad0;

    City** c = cities;
    u8 i = currentCity;
    for (; i > 0; i--, c++)
    { }

    
    City** targetCity = NULL;
    if (currentPackage != NULL)
    {
        targetCity = cities;
        i = 0;
        for (; i < currentPackage->to; i++)
        {
            targetCity++;
        }
    }

    if ((*c)->availablePackages == 0)
    {
        sprintf(debug_str, "%cNo package available", menuIndex == 0 ? '>' : ' ');
        canGetPackage = false;
    }
    else if (currentPackage != NULL)
    {
        sprintf(debug_str, "%cAlready have package", menuIndex == 0 ? '>' : ' ');
        canGetPackage = false;
    }
    else
    {
        sprintf(debug_str, "%cGet a package", menuIndex == 0 ? '>' : ' ');
        canGetPackage = true;
    }
    consoleDrawText(10, 20, debug_str);
    if (currentPackage == NULL)
    {
        sprintf(debug_str, "%cNothing to deliver", menuIndex == 1 ? '>' : ' ');
        canDeliverPackage = false;
    }
    else if (currentPackage->to != currentCity)
    {
        sprintf(debug_str, "%cDeliver to %s", menuIndex == 1 ? '>' : ' ', (*targetCity)->name);
        canDeliverPackage = false;
    }
    else
    {
        sprintf(debug_str, "%cDeliver a package", menuIndex == 1 ? '>' : ' ');
        canDeliverPackage = true;
    }
    consoleDrawText(10, 22, debug_str);
    sprintf(debug_str, "%cLeave", menuIndex == 2 ? '>' : ' ');
    consoleDrawText(10, 24, debug_str);
}

void World_SetScroll(bool forceRender)
{
    if (currentCity < U8_MAX)
    {
        RenderMenu();
        return;
    }

    short pad0 = padsCurrent(0);

    bool didMove = false;

    s16 lastX = playerX;
    s16 lastY = playerY;

    // Get inputs
    if (pad0 & KEY_UP)
    {
        playerY -= player_speed;
        if (playerY < TILE_SIZE) playerY = TILE_SIZE;
        didMove = true;
    }
    else if (pad0 & KEY_DOWN)
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
    else if (pad0 & KEY_LEFT)
    {
        playerX -= player_speed;
        if (playerX < TILE_SIZE) playerX = TILE_SIZE;
        didMove = true;
    }

    if (!didMove && !forceRender) return;

    u16 arrX = (u16)(playerX / TILE_SIZE);
    u16 arrY = (u16)(playerY / TILE_SIZE);
    u8 new_speed = GetSpeed(arrX, arrY);
    if (new_speed == U8_MAX)
    {
        City** c = cities;
        u8 i = 0;
        while (*c)
        {
            if (arrX == (*c)->x && arrY == (*c)->y)
            {
                sprintf(debug_str, (*c)->welcomeText);
                consoleDrawText(10, 6, debug_str);

                currentCity = i;
                menuIndex = 0;
                lastPad0 = 0;
                break;
            }
            c++;
            i++;
        }
        
        if (*c == NULL) // Not supposed to happen
        {
            sprintf(debug_str, "Unknown city found");
            consoleDrawText(10, 6, debug_str);
        }
        playerX = lastX;
        playerY = lastY;
        // Found a city!
        
        // Clear debug
        sprintf(debug_str, "                                 ");
        consoleDrawText(1, 20, debug_str);
        sprintf(debug_str, "                                 ");
        consoleDrawText(1, 22, debug_str);
        sprintf(debug_str, "                                 ");
        consoleDrawText(1, 24, debug_str);
        sprintf(debug_str, "                                 ");
        consoleDrawText(1, 26, debug_str);

        return;
    }
    if (new_speed == 0)
    {
        playerX = lastX;
        playerY = lastY;
        return; // Wall, we didn't move
    }

    player_speed = new_speed;

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
    consoleDrawText(1, 20, debug_str);
    sprintf(debug_str, "Local: %u ; %u     ", player.x, player.y);
    consoleDrawText(1, 22, debug_str);
    sprintf(debug_str, "Camera: %d ; %d     ", finalX, finalY);
    consoleDrawText(1, 24, debug_str);
    sprintf(debug_str, "Grid: %d ; %d     ", arrX, arrY);
    consoleDrawText(1, 26, debug_str);

    // Draw
    bgSetScroll(1, finalX, finalY);
    Entity_Draw(&player);
}