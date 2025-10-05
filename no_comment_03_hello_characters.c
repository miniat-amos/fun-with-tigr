/**
 * Program: 03_hello_characters
 * 
 * This program uses tigrReadChar() to detect printable character keypresses
 * and prints the most recent to the screen.  This function does not detect
 * "special key" presses (eg, Enter, arrow keys, fuction keys).  Instead,
 * it detects aplha numeric keys, symbols, and just a couple non-printable
 * characters, such as backspace and delete.
 */
#include "tigr.h"

int main(int argc, char *argv[]) {
    Tigr *screen = tigrWindow(300, 200, __FILE__, TIGR_FIXED);

    const char str[] = "Press 'regular' keyboard keys:";
    char key_str[] = " ";

    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
        char key = (char)tigrReadChar(screen);

        if(key != 0) {
            key_str[0] = key;
        }

        tigrClear(screen, tigrRGB(0xDD, 0xBB, 0xFF));
        tigrPrint(screen, tfont, 50, 75, tigrRGB(0xFF, 0xFF, 0xFF), str);
        tigrPrint(screen, tfont, 65, 90, tigrRGB(0xFF, 0xFF, 0xFF), key_str);
        tigrUpdate(screen);
    }

    tigrFree(screen);

    return 0;
}
