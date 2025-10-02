#include "tigr.h"

int main(int argc, char *argv[])
{
    Tigr *screen = tigrWindow(300, 200, "Hello, Window", TIGR_FIXED);

    tigrClear(screen, tigrRGB(0xDD, 0xBB, 0xFF));

    while (!tigrClosed(screen)) {
        tigrUpdate(screen);
    }

    tigrFree(screen);

    return 0;
}