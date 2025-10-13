/**
 * Program: 06_hello_drawing
 *
 * This program draws several shapes
 */
#include <stdio.h>
#include "tigr.h"

int main(int argc, char *argv[]) {

    Tigr *screen = tigrWindow(300, 200, __FILE__, TIGR_FIXED);

    const char str[] = "Here are some basic shapes!";

    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
        tigrClear(screen, tigrRGB(0x55, 0xBB, 0x55));

        tigrPrint(screen, tfont, 30, 60, tigrRGB(0xFF, 0xFF, 0xFF), str);

        tigrRect(screen, 30, 80, 70, 70, tigrRGB(0x00, 0x00, 0x00));
        tigrFillRect(screen, 30, 80, 70, 70, tigrRGB(0xFF, 0x80, 0x00));

        tigrFillCircle(screen, 150, 115, 35, tigrRGB(0xFF, 0xFF, 0x00));

        tigrLine(screen, 200, 80, 270, 150, tigrRGB(0x00, 0x00, 0x00));
        tigrLine(screen, 200, 150, 270, 80, tigrRGB(0x00, 0x00, 0x00));

        tigrUpdate(screen);
    }

    tigrFree(screen);

    return 0;
}
