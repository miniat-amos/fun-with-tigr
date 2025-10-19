/**
 * Program: 08_hello_bitmap
 *
 * This program draws several shapes on a bitmap, then displays it to a window.
 */
#include <stdio.h>
#include "tigr.h"

int main(int argc, char *argv[]) {

    Tigr *screen = tigrWindow(300, 200, __FILE__, TIGR_FIXED);

    /**
     * tigrBitmap() like tigrWindow() creates a Tigr object that we can
     * draw on. However, tigrBitmap() creates a bitmap that is not attached
     * to a window, acting as an off-screen canvas. We can use bitmaps to 
     * store pixel data without always rendering the results, or in the 
     * case here, drawing static shapes once on the bitmap and then drawing
     * the results to the windowed bitmap without redrawing each individual
     * shape each iteration.
     */
    Tigr *bitmap = tigrBitmap(300, 200);

    const char bitmap_str[] = "These were drawn on an off-screen bitmap!";
    const char window_str[] = "This text was drawn on the windowed bitmap!";

    /**
     * Same as in 06_hello_drawing, but drawn on the bitmap instead of the
     * windowed bitmap. Notice we are outside the main loop, pre-drawing the
     * shapes on bitmap for later use.
     */
    tigrClear(bitmap, tigrRGB(0x55, 0xBB, 0x55));

    tigrPrint(bitmap, tfont, 10, 60, tigrRGB(0xFF, 0xFF, 0xFF), bitmap_str);

    tigrRect(bitmap, 30, 80, 70, 70, tigrRGB(0x00, 0x00, 0x00));
    tigrFillRect(bitmap, 30, 80, 70, 70, tigrRGB(0xFF, 0x80, 0x00));

    tigrFillCircle(bitmap, 150, 115, 35, tigrRGB(0xFF, 0xFF, 0x00));

    tigrLine(bitmap, 200, 80, 270, 150, tigrRGB(0x00, 0x00, 0x00));
    tigrLine(bitmap, 200, 150, 270, 80, tigrRGB(0x00, 0x00, 0x00));

    /* We still use the windowed bitmap for the loop and inputs */
    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {

        /* Using tigrBlit() to draw the full bitmap to the entire screen */
        tigrBlit(screen, bitmap, 0, 0, 0, 0, bitmap->w, bitmap->h);

        /**
         * We can still draw things onto the screen and layer them on top of the
         * pre-drawn bitmap.
         */
        tigrPrint(screen, tfont, 10, 160, tigrRGB(0xFF, 0xFF, 0xFF), window_str);

        /**
         * We are only rendering to the active window, which means we update only
         * the windowed Tigr object, not the bitmap.
         */ 
        tigrUpdate(screen);
    }

    tigrFree(screen);
    /* Like the screen, cleanly free resources associated with the bitmap */
    tigrFree(bitmap);

    return 0;
}
