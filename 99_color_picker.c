/**
 * Program: 99_color_picker.c
 * 
 * This program shows a HSL/HSV color palette and allows the user to view the
 * RGB values of the cursor position. Within this file contains tigrRGB 
 * compatible helper functions for creating TPixels using HSL/HSV values.
 */

#include "tigr.h"
#include <stdio.h>
#include <math.h>

#define GRAD_W          360
#define GRAD_H          100
#define FONT_H          12
#define SWATCH_S        FONT_H * 3
#define SCREEN_W        GRAD_W
#define SCREEN_H        GRAD_H + SWATCH_S
#define GREET_OFFSET    20
#define MAX_SWATCHES    6
#define SWATCH_X_OFFSET 110
#define S_INC           0.01
#define STR_SIZE        100

/**
 * Internal calculation for creating RGB colors from a given hue, chroma, and
 * match value. Common between both HSL and HSV after the chroma and match
 * values are found. This creates the actual TPixel objects.
 */
TPixel tigrHSX_internal(int h, double c, double m)
{
    //https://en.wikipedia.org/wiki/HSL_and_HSV#To_RGB

    // Bounding h to 0-360
    h = h % 360;
    if (h < 0) h += 360;

    double h_prime = ((double) h / 60.0);
    double x = c * (1.0 - fabs(fmod(h_prime, 2.0) - 1.0));

    double r = 0, g = 0, b = 0;

    if (h_prime >= 0 && h_prime < 1) {
        r = c; g = x; b = 0;
    } else if (h_prime >= 1 && h_prime < 2) {
        r = x; g = c; b = 0;
    } else if (h_prime >= 2 && h_prime < 3) {
        r = 0; g = c; b = x;
    } else if (h_prime >= 3 && h_prime < 4) {
        r = 0; g = x; b = c;
    } else if (h_prime >= 4 && h_prime < 5) {
        r = x; g = 0; b = c;
    } else if (h_prime >= 5 && h_prime < 6) {
        r = c; g = 0; b = x;
    }

    TPixel p;
    p.r = fmin(0xFF, fmax(0, (r + m) * 0xFF));
    p.g = fmin(0xFF, fmax(0, (g + m) * 0xFF));
    p.b = fmin(0xFF, fmax(0, (b + m) * 0xFF));
    p.a = 0xFF;
    return p;
}

/**
 * Function for creating TPixels from HSV values. Compatible with tigrRGB().
 */
TIGR_INLINE TPixel tigrHSV(int h, double s, double v)
{
    // Chroma Calculation
    double c = v * s;
    // Value component
    double m = v - c;

    return tigrHSX_internal(h, c, m);
}

/**
 * Function for creating TPixels from HSL values. Compatible with tigrRGB().
 */
TIGR_INLINE TPixel tigrHSL(int h, double s, double l)
{
    // Chroma Calculation
    double c = (1 - fabs((2 * l) - 1)) * s;
    // Lightness component
    double m = l - (c / 2.0);

    return tigrHSX_internal(h, c, m);
}

/**
 * TPixel color inverter
 */
TPixel tigrInvert(TPixel pix){
    pix.r = 0xFF - pix.r;
    pix.g = 0xFF - pix.g;
    pix.b = 0xFF - pix.b;
    return pix;
}

enum ColorMode {
    HSL,
    HSV
};

/**
 * Draws HSL/HSV color gradient on to a 360x100 bitmap at a given level of
 * staturation, x-axis is the hue and the y-axis is the lightness/value.
 */
void drawHSXGrad(Tigr *btmp, double s, enum ColorMode mode)
{
    if(btmp->w != GRAD_W || btmp->h != GRAD_H) {
        printf("ERROR: Bitmap must be of size %dx%d for displaying HSX gradient!\n", GRAD_W, GRAD_H);
        return;
    }

    for(int y = 0; y < btmp->h; y++){
        for(int x = 0; x < btmp->w; x++){
            switch (mode)
            {
            case HSL:
                tigrPlot(btmp, x, y, tigrHSL(x, s, (double)y / (double)btmp->h));
                break;
            case HSV:
                tigrPlot(btmp, x, y, tigrHSV(x, s, (double)y / (double)btmp->h));
                break;
            default:
                break;
            }
        }
    }
}

/**
 * Draws palette given current swatch colors on to a given bitmap
 */
void drawPalette(Tigr *btmp, TPixel swatches[MAX_SWATCHES], int cur_swatch)
{
    if(btmp->w != MAX_SWATCHES *  SWATCH_S || btmp->h != SWATCH_S) {
        printf("ERROR: Bitmap must be of size %dx%d for displaying palette!\n", MAX_SWATCHES *  SWATCH_S, SWATCH_S);
        return;
    }

    int h = btmp->h;
    char hex_str[STR_SIZE];

    for(int i = 0; i < MAX_SWATCHES; i++){
        tigrFill(btmp, i * h, 0, h, h, swatches[i]);
        snprintf(hex_str, STR_SIZE, "0x%02X\n0x%02X\n0x%02X", swatches[i].r, swatches[i].g, swatches[i].b);
        tigrPrint(btmp, tfont, i * h, 0, tigrRGB(0xFF, 0xFF, 0xFF), hex_str);

        if (cur_swatch == i) {
            tigrLine(btmp, i * h, h-1, (i*h) + h, h-1, tigrInvert(swatches[i]));
        }
    }
}

int main(int argc, char *argv[]) 
{
    /**
     * Mouse variables
     */
    int mx;
    int my;
    int mb;
    int prev_mb = 0;

    /**
     * Strings for storing color info
     */
    char hsx_str[STR_SIZE];
    char rgb_str[STR_SIZE];
    char hex_str[STR_SIZE];

    const char title[] = __FILE__;
    const char greeting[] = "Welcome to the Fun Color Picker\n - Mouse position to select color\n - Click to add color to palette\n - 'c' to clear palette\n - 'Space' to switch between HSL and HSV\n - 'Up' & 'Down' to change saturation\n Press space to close this menu...";

    /* Starting saturation */
    double s = 1.0;

    enum ColorMode mode = HSL;

    TPixel target_pixel;

    /**
     * Setup all bitmaps
     */
    Tigr *screen = tigrWindow(SCREEN_W, SCREEN_H, title, TIGR_FIXED);
    Tigr *gradient = tigrBitmap(GRAD_W, GRAD_H);
    Tigr *swatch = tigrBitmap(SWATCH_S, SWATCH_S);
    Tigr *palette = tigrBitmap(SWATCH_S * MAX_SWATCHES, SWATCH_S);

    /**
     * Create list of stored colors and fill it with black initially
     */
    TPixel swatches[MAX_SWATCHES];
    for (int i = 0; i < MAX_SWATCHES; i++)
        swatches[i] = tigrRGB(0x00,0x00,0x00);
    int cur_swatch = 0;

    /**
     * Fill bitmaps with their initial information
     */
    drawHSXGrad(gradient, s, mode);
    tigrFill(swatch, 0,0, swatch->w, swatch->h, tigrRGB(0xFF, 0xFF, 0xFF));
    drawPalette(palette, swatches, cur_swatch);

    /**
     * Layout bitmaps in their correct locations
     */
    tigrBlit(screen, gradient, 0, 0, 0, 0, gradient->w, gradient->h);
    tigrBlit(screen, swatch, SWATCH_X_OFFSET, gradient->h, 0, 0, swatch->w, swatch->h);
    tigrBlit(screen, palette, SWATCH_X_OFFSET + swatch->w, gradient->h, 0, 0, palette->w, palette->h);

    /**
     * Show welcome message with rectangle background, offset from the screen edges
     */
    tigrFillRect(screen, GREET_OFFSET, GREET_OFFSET, screen->w - (GREET_OFFSET * 2), screen->h - (GREET_OFFSET * 2), tigrRGB(0x55, 0xBB, 0x55));
    tigrRect(screen, GREET_OFFSET, GREET_OFFSET, screen->w - (GREET_OFFSET * 2), screen->h - (GREET_OFFSET * 2), tigrRGB(0x00, 0x00, 0x00));
    tigrPrint(screen, tfont, GREET_OFFSET + 2, GREET_OFFSET + 2, tigrRGB(0xFF, 0xFF, 0xFF), greeting);

    tigrUpdate(screen);

    /**
     * Hold user hostage until they press space, escape, or close window
     */
    while(!tigrKeyDown(screen, TK_SPACE) && !tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE))
        tigrUpdate(screen);

    while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {

        /** 
         * Use space to control HSL vs HSV as a toggle
         */
        if (tigrKeyDown(screen,TK_SPACE) && mode == HSL){
            mode = HSV;
            drawHSXGrad(gradient, s, mode);
        } else if (tigrKeyDown(screen,TK_SPACE) && mode == HSV){
            mode = HSL;
            drawHSXGrad(gradient, s, mode);
        }

        /**
         * Clear all saved palette swatches when user presses 'c'
         */
        if ((char)tigrReadChar(screen) == 'c'){
            for (int i = 0; i < MAX_SWATCHES; i++)
                swatches[i] = tigrRGB(0x00,0x00,0x00);
            cur_swatch = 0;
            drawPalette(palette, swatches, cur_swatch);
        }

        /**
         * Increment/decrement saturation 
         * Update gradient bitmap on changes 
         */
        if(tigrKeyHeld(screen, TK_UP) && s < 1.0){
            s += S_INC;
            drawHSXGrad(gradient, s, mode);
        }  
        if(tigrKeyHeld(screen, TK_DOWN) && s > 0.0){
            s -= S_INC;
            drawHSXGrad(gradient, s, mode);
        }

        /** 
         * Mouse controls, bounding values to be within window 
         */
        tigrMouse(screen, &mx, &my, &mb);
        if (mx < 0) mx = 0;
        if (mx >= gradient->w) mx = gradient->w - 1;
        if (my < 0) my = 0;
        if (my >= gradient->h) my = gradient->h - 1;

        /* Get the pixel under mouse */
        target_pixel = gradient->pix[my * gradient->w + mx];
        
        /** 
         * On *click* add a color to the saved colors
         * If maxed, wrap around 
         */
        if (mb == 1 && prev_mb == 0 && cur_swatch < MAX_SWATCHES) {

            swatches[cur_swatch] = target_pixel;
            cur_swatch++;

            if (cur_swatch  >= MAX_SWATCHES)
                cur_swatch = 0;

            drawPalette(palette, swatches, cur_swatch);
        }
        prev_mb = mb;

        /* Get hue for display */
        int h = (mx * 360) / screen->w;

        /* Get color value/lightness calculation for display */
        double vl = ((double)my / gradient->h );

        /**
         * Generate strings for color info 
         */
        char letter;
        if (mode == HSV)
            letter = 'V';
        else
            letter = 'S';
        snprintf(hsx_str, STR_SIZE, "H:%03d S:%03.0lf %c:%03.0lf", h, s*100, letter, vl*100);
    
        int r = target_pixel.r;
        int g = target_pixel.g;
        int b = target_pixel.b;
        snprintf(rgb_str, STR_SIZE, "R:%03d G:%03d B:%03d", r, g, b);

        snprintf(hex_str, STR_SIZE, "0x%02X 0x%02X 0x%02X", r, g, b);

        /* Clear bottom of screen */
        tigrFill(screen,
            0, gradient->h,
            screen->w, screen->w - gradient->h,
            tigrRGB(0x00,0x00,0x00)
        );

        /* Fill swatch with curent color */
        tigrFill(swatch, 0,0, swatch->w, swatch->h, target_pixel);

        /* Blit all bitmaps on to the screen */
        tigrBlit(screen, gradient, 0, 0, 0, 0, gradient->w, gradient->h);
        tigrBlit(screen, swatch, SWATCH_X_OFFSET, gradient->h, 0, 0, swatch->w, swatch->h);
        tigrBlit(screen, palette, SWATCH_X_OFFSET + swatch->w, gradient->h, 0, 0, palette->w, palette->h);
        
        /* Text display */
        tigrPrint(screen, tfont, 0, gradient->h, tigrRGB(0xFF, 0xFF, 0xFF), hsx_str);
        tigrPrint(screen, tfont, 0, tfont->glyphs->h + gradient->h, tigrRGB(0xFF, 0xFF, 0xFF), rgb_str);
        tigrPrint(screen, tfont, 0, (tfont->glyphs->h * 2) + gradient->h, tigrRGB(0xFF, 0xFF, 0xFF), hex_str);

        tigrUpdate(screen);
    }

    /**
     * Free everything
     */
    tigrFree(screen);
    tigrFree(gradient);
    tigrFree(swatch);
    tigrFree(palette);

    return 0;
}