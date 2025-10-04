/**
 * Program: 00_hello_window
 * 
 * This program opens a window in TIGR_FIXED mode... ie, the window is
 * made as large as possible to contain an integer-scaled version of
 * its bitmap surface. Resizing the window will scale the bitmap in
 * integer steps and letterbox it.  The 300x200 bitmap is cleared
 * to the color DataBase Fabulous... courtesy of Leroy.
 * 
 * Search tigr.h for TIGR_FIXED to find additional window modes.
 */
#include "tigr.h"

/**
 * A useful macro defined in standard C is __FILE__.  It is always
 * replaced with a string that is the name of the file it is in,
 * in this case, __FILE__ is the string "00_hello_window.c".
 */
const char title[] = __FILE__;  // a title for the window

int main(int argc, char *argv[]) {
    /**
     * tigrWindow() creates a window with given attributes and returns
     * a reference to the internal bitmap that window shows.
     */
    Tigr *screen = tigrWindow(300, 200, title, TIGR_FIXED);

    /* Fill the window bitmap with DataBase Fabulous */
    tigrClear(screen, tigrRGB(0xDD, 0xBB, 0xFF));

    /* Until the window is closed (eg, click the 'X') */
    while (!tigrClosed(screen)) {
        /**
         * Render any changes that were made to the screen's internal
         * bitmap since the last tigrUpdate().  Also, this allows
         * events to be detected and acted upon... without it,
         * clicking the 'X' in the title bar won't even close the
         * window.
         */
        tigrUpdate(screen);
    }

    /* Cleanly free resources associated with the window's bitmap */
    tigrFree(screen);

    return 0;
}
