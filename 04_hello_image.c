/**
 * Program: 04_hello_image
 *
 * This program loads the Fun with TIGR logo image and displays it
 * centered on the window.
 */
#include "tigr.h"

int main(int argc, char *argv[]) {
    Tigr *screen = tigrWindow(300, 200, __FILE__, TIGR_FIXED);

    /**
     * tigr_LoadImage() loads a PNG file into a TIGR bitmap.
     * Note the data type, Tigr *, is the same as the screen
     * variable that represents the window of the program.  The
     * Tigr data type is essentially a bitmap, the screen
     * bitmap just maintains a handle (a sort of reference number)
     * to the window we created with tigrWindow().
     */
    Tigr *fun_tigr = tigrLoadImage("assets/fun_with_tigr.png");

    /**
     * Find the top-left X,Y that would center the logo on screen
     */
    int left = ((screen->w - fun_tigr->w) / 2);
    int top = ((screen->h - fun_tigr->h) / 2);

    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
        tigrClear(screen, tigrRGB(0x55, 0xBB, 0x55));

        /**
         * tigrBlit() copies part of a TIGR bitmap to another
         * bitmap.  The top-left of the destination bitmap is given
         * along with top-left and width/height of the part of the
         * source bitmap you want to copy over.  This is known in
         * the graphics world as a "block transfer", "blit" for short.
         *
         * Check out tigrBlitAlpha() if you want to use images with
         * transparency or to blend in a totally opaque image.
         */
        tigrBlit(screen, fun_tigr, left, top, 0, 0, fun_tigr->w, fun_tigr->h);
        tigrUpdate(screen);
    }

    tigrFree(screen);
    tigrFree(fun_tigr);

    return 0;
}
