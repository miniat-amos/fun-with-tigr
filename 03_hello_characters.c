/**
 * Program: 03_hello_characters
 *
 * This program use TIGR to detect printable character keypresses
 * and prints the most recent to the screen.  This approach does not detect
 * "special key" presses (eg, Enter, arrow keys, fuction keys).  Instead,
 * it detects aplha numeric keys, symbols, and just a couple non-printable
 * characters, such as backspace and delete.
 */
#include "tigr.h"

int main(int argc, char *argv[]) {
    Tigr *screen = tigrWindow(300, 200, __FILE__, TIGR_FIXED);

    const char str[] = "Press 'regular' keyboard keys:";
    /**
     * This string will be where we store the most recent character pressed.
     * Every frame, we'll show this on the screen, so we initialize it to
     * space (something we can't see) so before any key has been pressed,
     * the program will appear to not be printing anything about a key.
     */
    char key_str[] = " ";

    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
        char key = (char)tigrReadChar(screen);
        /**
         * tigrReadChar() returns 0 if no key has been pressed, so wait
         * until its return indicates a key has been presseed.
         */
        if(key != 0) {
            /* A new key was detected.  Make it the one we show now. */
            key_str[0] = key;
        }

        tigrClear(screen, tigrRGB(0x55, 0xBB, 0x55));
        tigrPrint(screen, tfont, 30, 60, tigrRGB(0xFF, 0xFF, 0xFF), str);
        tigrPrint(screen, tfont, 45, 75, tigrRGB(0xFF, 0xFF, 0xFF), key_str);
        tigrUpdate(screen);
    }

    tigrFree(screen);

    return 0;
}
