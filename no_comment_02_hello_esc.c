/**
 * Program: no_comment_02_hello_esc
 *
 * This program shows how to detect the ESC key and one way a
 * program could terminate when that happens.
 */
#include "tigr.h"

const char str[] = "Press the ESC key to exit...";

int main(int argc, char *argv[]) {
    Tigr *screen = tigrWindow(300, 200, __FILE__, TIGR_FIXED);

    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
        tigrClear(screen, tigrRGB(0x55, 0xBB, 0x55));

        tigrPrint(screen, tfont, 30, 60, tigrRGB(0xFF, 0xFF, 0xFF), str);
        tigrUpdate(screen);
    }

    tigrFree(screen);

    return 0;
}
