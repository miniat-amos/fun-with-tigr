/**
 * Program: 01_hello_font
 *
 * This program uses the builtin TIGR font to draw some text to the screen.
 * Notice that the string used has a newline in the middle, and TIGR
 * uses this to print the string across two visible lines.
 */
#include "tigr.h"

const char str[] = "Hello, font...\nTIGR has a nice builtin font.";

int main(int argc, char *argv[]) {
    Tigr *screen = tigrWindow(300, 200, __FILE__, TIGR_FIXED);

    while (!tigrClosed(screen)) {
        tigrClear(screen, tigrRGB(0x55, 0xBB, 0x55));

        tigrPrint(screen, tfont, 30, 60, tigrRGB(0xFF, 0xFF, 0xFF), str);

        tigrUpdate(screen);
    }

    tigrFree(screen);

    return 0;
}
