/**
 * Program: no_comment_04_hello_image
 *
 * This program loads the Fun with TIGR logo image and displays it
 * centered on the window.
 */
#include "tigr.h"

int main(int argc, char *argv[]) {
    Tigr *screen = tigrWindow(300, 200, __FILE__, TIGR_FIXED);

    Tigr *fun_tigr = tigrLoadImage("assets/fun_with_tigr.png");

    int left = ((screen->w - fun_tigr->w) / 2);
    int top = ((screen->h - fun_tigr->h) / 2);

    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
        tigrClear(screen, tigrRGB(0x55, 0xBB, 0x55));

        tigrBlit(screen, fun_tigr, left, top, 0, 0, fun_tigr->w, fun_tigr->h);
        tigrUpdate(screen);
    }

    tigrFree(screen);
    tigrFree(fun_tigr);

    return 0;
}
