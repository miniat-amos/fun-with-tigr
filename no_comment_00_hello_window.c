/**
 * Program: no_comment_00_hello_window
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

const char title[] = __FILE__;

int main(int argc, char *argv[]) {
    Tigr *screen = tigrWindow(300, 200, title, TIGR_FIXED);

    tigrClear(screen, tigrRGB(0x55, 0xBB, 0x55));

    while (!tigrClosed(screen)) {
        tigrUpdate(screen);
    }

    tigrFree(screen);

    return 0;
}
