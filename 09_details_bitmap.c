/**
 * Program: 09_details_bitmap
 *
 * This program opens a canvas for the user to draw on, allowing the resulting
 * bitmap to be saved. It shows the use of an off-screen bitmap for containing
 * pixel information independent from the active window, using the active
 * window for managing inputs, and correcting between absolute window
 * coordinates and local bitmap coordinates.
 * 
 * Because the drawing canvas is kept separate, we are able to easily save just
 * the drawing and not the entire window's bitmap. 
 */
#include <stdio.h>
#include "tigr.h"

int main(int argc, char *argv[]) {

    /**
     *  Setup Bitmaps
     */
    Tigr *screen = tigrWindow(300, 200, __FILE__, TIGR_FIXED);
    Tigr *canvas = tigrBitmap(150, 150);

    /**
     * Offset for rendering the canvas to the center. We use this for both blit
     * coordinates, as well as correctly drawing pixels to the canvas.
     */
    int c_offset_x = (screen->w - canvas->w) / 2;
    int c_offset_y = (screen->h - canvas->h) / 2;

    /**
     * Mouse button variables
     */
    int mx;
    int my;
    int mbuttons;

    /* Color for drawing */
    TPixel black = tigrRGB(0x00, 0x00, 0x00);
    
    const char message[] = "Use left mouse button to draw, 'c' to clear,\n's' to save!";

    /* Name for saving the drawing */
    const char save_name[] = "my_fun_drawing.png";

    /* Give initial color to canvas before main loop */
    tigrClear(canvas, tigrRGB(0xFF, 0xFF, 0xFF));

    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {

        char key = (char)tigrReadChar(screen);

        tigrMouse(screen, &mx, &my, &mbuttons);
        
        /**
         * When user presses 's', save the canvas bitmap. Notice that the saved
         * file does not contain the text that is rendered over it while the
         * program is active. The canvas bitmap contains only the information
         * created from the user drawing and we copy that information to the
         * screen's bitmap. We use the screen to handle inputs and show the
         * result. 
         */
        if(key == 's'){
            tigrSaveImage(save_name, canvas);
            printf("Drawing saved under '%s'\n", save_name);
        }

        /**
         * 'c' to clear the canvas
         */
        if(key == 'c'){
            tigrClear(canvas, tigrRGB(0xFF, 0xFF, 0xFF));
        }

        /**
         * When the user clicks, we begin drawing by creating small circles
         * at the cursor's location. Because the window is larger than the
         * canvas and we are centering the canvas, we must subtract by the
         * offset used for centering. This corrects the absolute mouse screen
         * coordinates to the local canvas coordinates and allows us to color
         * the proper pixels.
         */
        if(mbuttons == 1){
            int cx = mx - c_offset_x;
            int cy = my - c_offset_y;

            tigrFillCircle(canvas, cx, cy, 3, black);
        }

        /* Clear screen, NOT the canvas */
        tigrClear(screen, tigrRGB(0x55, 0xBB, 0x55));

        /* Center the canvas in the screen */
        tigrBlit(screen, canvas, c_offset_x, c_offset_y, 0, 0, canvas->w, canvas->h);

        tigrPrint(screen, tfont, 5, 160, tigrRGB(0xDD, 0xDD, 0xDD), message);

        tigrUpdate(screen);
    }

    tigrFree(screen);
    tigrFree(canvas);

    return 0;
}
