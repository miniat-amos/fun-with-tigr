/**
 * Program: 09_details_bitmap
 *
 * This program opens a canvas for the user to draw on, allowing the resulting
 * bitmap to be saved. It shows the use of an off-screen bitmap for containing
 * pixel information independent from the active window, using the active
 * window for managing inputs, and correcting between absolute window
 * coordinates and local bitmap coordinates. 
 */
#include <stdio.h>
#include "tigr.h"

int main(int argc, char *argv[]) {

    Tigr *screen = tigrWindow(300, 200, __FILE__, TIGR_FIXED);
    Tigr *canvas = tigrBitmap(150, 150);

    int c_offset_x = (screen->w - canvas->w) / 2;
    int c_offset_y = (screen->h - canvas->h) / 2;

    int mx;
    int my;
    int mbuttons;

    TPixel black = tigrRGB(0x00, 0x00, 0x00);
    
    const char message[] = "Use left mouse button to draw, 'c' to clear,\n's' to save!";

    const char save_name[] = "my_fun_drawing.png";

    tigrClear(canvas, tigrRGB(0xFF, 0xFF, 0xFF));

    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {

        char key = (char)tigrReadChar(screen);

        tigrMouse(screen, &mx, &my, &mbuttons);

        
        if(key == 's'){
            tigrSaveImage(save_name, canvas);
            printf("Drawing saved under '%s'\n", save_name);
        }

        if(key == 'c'){
            tigrClear(canvas, tigrRGB(0xFF, 0xFF, 0xFF));
        }

        if(mbuttons == 1){
            int cx = mx - c_offset_x;
            int cy = my - c_offset_y;

            tigrFillCircle(canvas, cx, cy, 3, black);
        }


        tigrClear(screen, tigrRGB(0x55, 0xBB, 0x55));

        tigrBlit(screen, canvas, c_offset_x, c_offset_y, 0, 0, canvas->w, canvas->h);

        tigrPrint(screen, tfont, 5, 160, tigrRGB(0xDD, 0xDD, 0xDD), message);

        tigrUpdate(screen);
    }

    tigrFree(screen);
    tigrFree(canvas);

    return 0;
}
