/**
 * Program: 01_hello_font
 * 
 * This program uses the builtin TIGR font to draw some text to the screen.
 * Notice that the string used has a newline in the middle, and TIGR
 * uses this to print the string across two visible lines.
 */
#include "tigr.h"

const char title[] = "01_hello_font";  // a title for the window
const char str[] = "Hello, font...\nTIGR has a nice builtin font.";

int main(int argc, char *argv[]) {
    Tigr *screen = tigrWindow(300, 200, title, TIGR_FIXED);

    while (!tigrClosed(screen)) {
        tigrClear(screen, tigrRGB(0xDD, 0xBB, 0xFF));
        
        /* Use the builtin TIGR font to draw some text */
        tigrPrint(screen, tfont, 50, 75, tigrRGB(0xFF, 0xFF, 0xFF), str);
        
        tigrUpdate(screen);
    }

    tigrFree(screen);

    return 0;
}
