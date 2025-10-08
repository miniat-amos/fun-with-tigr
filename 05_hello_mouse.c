/**
 * Program: 05_hello_mouse
 *
 * This program shows the current mouse X, Y coordinates along with
 * the mouse button states.
 */
#include <stdio.h>  // for snprintf()
#include "tigr.h"

int main(int argc, char *argv[]) {
    /**
     * These will track the mouse position and button state.
     */
    int x;
    int y;
    int buttons;

    /**
     * For generating the string about the mouse state
     */
    const int size = 30;
    char mouse_str[size];

    Tigr *screen = tigrWindow(300, 200, __FILE__, TIGR_FIXED);

    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
        /**
         * Capture the mouse state using tigrMouse().  To get the three desired
         * values from this function, references to each are used as output
         * parameters.
         */
        tigrMouse(screen, &x, &y, &buttons);

        /**
         * Format the mouse position and buttons pressed into a string to print
         * on the screen.
         */
        snprintf(mouse_str, size, "(%4d, %4d) with button: %d", x, y, buttons);

        tigrClear(screen, tigrRGB(0x55, 0xBB, 0x55));
        tigrPrint(screen, tfont, 50, 75, tigrRGB(0xFF, 0xFF, 0xFF), mouse_str);
        tigrUpdate(screen);
    }

    tigrFree(screen);

    return 0;
}
