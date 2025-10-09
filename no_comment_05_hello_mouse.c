/**
 * Program: 05_hello_mouse
 *
 * This program shows the current mouse X, Y coordinates along with
 * the mouse button states.
 */
#include <stdio.h>
#include "tigr.h"

int main(int argc, char *argv[]) {
    int x;
    int y;
    int buttons;

    const int size = 30;
    char mouse_str[size];

    Tigr *screen = tigrWindow(300, 200, __FILE__, TIGR_FIXED);

    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
        tigrMouse(screen, &x, &y, &buttons);

        snprintf(mouse_str, size, "(%4d, %4d) with button: %d", x, y, buttons);

        tigrClear(screen, tigrRGB(0x55, 0xBB, 0x55));
        tigrPrint(screen, tfont, 30, 60, tigrRGB(0xFF, 0xFF, 0xFF), mouse_str);
        tigrUpdate(screen);
    }

    tigrFree(screen);

    return 0;
}
