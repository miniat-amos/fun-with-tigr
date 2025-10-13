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

        /**
         * tigrRect() draws the outline only of a rectangle
         * tigrFillRect() draws the fill area of a rectangle, but notice
         * that we're drawing the fill after the outline, but it doesn't
         * cover the outline.  That's because this function fills the
         * rectangle from the given coordinates one pixel in from the
         * edge pixels of the coordinate arguments.
         */
        tigrRect(screen, 30, 80, 70, 70, tigrRGB(0x00, 0x00, 0x00));
        tigrFillRect(screen, 30, 80, 70, 70, tigrRGB(0xFF, 0x80, 0x00));

        /**
         * Like tigrFillRect(), tigrFillCircle() on fills the pixels
         * of the circle just inside the one provided by the
         * coordinate arguments.  It's important to note that circles
         * are defined by their center instead of their corners.
         */
        tigrFillCircle(screen, 150, 115, 35, tigrRGB(0xFF, 0xFF, 0x00));

        /**
         * Draw two lines to make an 'X'.  You can make a ton of images
         * with just these few drawing functions.
         */
        tigrLine(screen, 200, 80, 270, 150, tigrRGB(0x00, 0x00, 0x00));
        tigrLine(screen, 200, 150, 270, 80, tigrRGB(0x00, 0x00, 0x00));

        tigrUpdate(screen);
    }

    tigrFree(screen);

    return 0;
}
