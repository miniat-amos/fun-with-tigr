/**
 * Program: no_comment_08_hello_bitmap
 *
 * This program draws several shapes on a bitmap, then displays it to a window.
 */
#include <stdio.h>
#include "tigr.h"

int main(int argc, char *argv[]) {

    Tigr *screen = tigrWindow(300, 200, __FILE__, TIGR_FIXED);
    Tigr *bitmap = tigrBitmap(300, 200);

    const char bitmap_str[] = "This is on a bitmap!";
    const char window_str[] = "This is on a window!";

    tigrClear(bitmap, tigrRGB(0x55, 0xBB, 0x55));

    tigrPrint(bitmap, tfont, 30, 60, tigrRGB(0xFF, 0xFF, 0xFF), bitmap_str);

    tigrRect(bitmap, 30, 80, 70, 70, tigrRGB(0x00, 0x00, 0x00));
    tigrFillRect(bitmap, 30, 80, 70, 70, tigrRGB(0xFF, 0x80, 0x00));

    tigrFillCircle(bitmap, 150, 115, 35, tigrRGB(0xFF, 0xFF, 0x00));

    tigrLine(bitmap, 200, 80, 270, 150, tigrRGB(0x00, 0x00, 0x00));
    tigrLine(bitmap, 200, 150, 270, 80, tigrRGB(0x00, 0x00, 0x00));

    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {

        tigrBlit(screen, bitmap, 0, 0, 0, 0, bitmap->w, bitmap->h);

        tigrPrint(screen, tfont, 160, 160, tigrRGB(0xFF, 0xFF, 0xFF), window_str);

        tigrUpdate(screen);
    }

    tigrFree(screen);
    tigrFree(bitmap);

    return 0;
}
