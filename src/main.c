#include <snes.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

extern char tilfont, palfont;

static unsigned int _playerX = INT_MAX / 2, _playerY = INT_MAX / 2;

//---------------------------------------------------------------------------------
int main(void)
{
    // Initialize text console with our font
    consoleSetTextMapPtr(0x6800);
    consoleSetTextGfxPtr(0x3000);
    consoleSetTextOffset(0x0100);
    consoleInitText(0, 16 * 2, &tilfont, &palfont);

    // Init background
    bgSetGfxPtr(0, 0x2000);
    bgSetMapPtr(0, 0x6800, SC_32x32);

    // Now Put in 16 color mode and disable Bgs except current
    setMode(BG_MODE1, 0);
    bgSetDisable(1);
    bgSetDisable(2);

    // Wait for nothing :P
    setScreenOn();

    short pad0;

    while (1)
    {
        // Get inputs
        pad0 = padsCurrent(0);

        if (pad0 & KEY_UP) _playerY++;
        if (pad0 & KEY_DOWN) _playerY--;
        if (pad0 & KEY_RIGHT) _playerX++;
        if (pad0 & KEY_LEFT) _playerX--;

        char str[50];
        sprintf(str, "%u ; %u     ", _playerX, _playerY);
        consoleDrawText(10, 10, str);

        WaitForVBlank();
    }
    return 0;
}