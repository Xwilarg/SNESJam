#include <snes.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "world.h"
#include "entity.h"
#include "config.h"

extern char tilfont, palfont;

extern char gfxpsrite, gfxpsrite_end;
extern char palsprite;

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

    // Init background
    bgSetGfxPtr(0, 0x2000);
    bgSetMapPtr(0, 0x6800, SC_32x32);

    // Now Put in 16 color mode and disable Bgs except current
    setMode(BG_MODE1, 0);
    bgSetDisable(2);

    // Wait for nothing :P
    setScreenOn();

    bool isFirstRender = true;

    while (1)
    {
        World_SetScroll(isFirstRender);
        isFirstRender = false;

        WaitForVBlank();
    }

    return 0;
}