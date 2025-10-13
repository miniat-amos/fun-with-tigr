/**
 * Program: 07_hello_fill
 *
 * This program shows how the TIGR "Fill" functions do NOT fill to
 * the full dimensions of the shape.  They fill the space one pixel
 * inside whatever you provide as arguments.  We'll draw a row of
 * rectangles and a row of circles, but the dimensions we use
 * describe shapes that should otherwise butt up against one
 * another on their sides.
 */
#include <stdio.h>
#include "tigr.h"

int main(int argc, char *argv[]) {

    Tigr *screen = tigrWindow(300, 200, __FILE__, TIGR_FIXED);

    const char str[] = "Filled shapes do not fill all the way.";

    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
        tigrClear(screen, tigrRGB(0x55, 0xBB, 0x55));

        tigrPrint(screen, tfont, 30, 60, tigrRGB(0xFF, 0xFF, 0xFF), str);

        for(int i = 0; i < 5; i++) {
            tigrFillRect(screen, i * 60, 80, 60, 40, tigrRGB(0xFF, 0x88, 0x00));
        }

        for(int i = 0; i < 10; i++) {
            tigrFillCircle(screen, (i * 30) + 15, 135, 15, tigrRGB(0xFF, 0xFF, 0x00));
        }

        tigrUpdate(screen);
    }

    tigrFree(screen);

    return 0;
}
