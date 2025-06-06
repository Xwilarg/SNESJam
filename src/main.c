#include <snes.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "world.h"
#include "entity.h"

extern char tilfont, palfont;

extern char gfxpsrite, gfxpsrite_end;
extern char palsprite;

static Entity player;

//---------------------------------------------------------------------------------
int main(void)
{
    consoleInit();

    oamInitGfxSet(&gfxpsrite, (&gfxpsrite_end - &gfxpsrite), &palsprite, 0, 0, 0x0000, OBJ_SIZE16_L32);

    // Initialize text console with our font
    consoleSetTextMapPtr(0x6800);
    consoleSetTextGfxPtr(0x3000);
    consoleSetTextOffset(0x0100);
    consoleInitText(0, 16 * 2, &tilfont, &palfont);

    World_Init();
    u16 worldSize = World_GetSize();
    u16 startPos = worldSize / 2;
    Entity_Init(&player, 0, startPos, startPos);

    // Init background
    bgSetGfxPtr(0, 0x2000);
    bgSetMapPtr(0, 0x6800, SC_32x32);

    // Now Put in 16 color mode and disable Bgs except current
    setMode(BG_MODE1, 0);
    bgSetDisable(2);

    // Wait for nothing :P
    setScreenOn();

    short pad0;

    while (1)
    {
        // Get inputs
        pad0 = padsCurrent(0);

        if (pad0 & KEY_UP && player.y > 0) player.y--;
        if (pad0 & KEY_DOWN && player.y < worldSize) player.y++;
        if (pad0 & KEY_RIGHT && player.x < worldSize) player.x++;
        if (pad0 & KEY_LEFT && player.x > 0) player.x--;

        char str[50];
        sprintf(str, "%u ; %u     ", player.x, player.y);
        consoleDrawText(10, 10, str);

        World_SetScroll(player.x, player.y);
        Entity_Draw(&player);

        WaitForVBlank();
    }

    return 0;
}