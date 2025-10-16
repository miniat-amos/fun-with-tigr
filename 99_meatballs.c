/**
 * This is a fun twist on a classic metaball demo, and so
 * we will can them meatballs, instead :-)
 */
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "tigr.h"

typedef enum {
    MEAT_MODE_SOLID = 0,  // draws somewhat traditional meatballs
    MEAT_MODE_HOLE,       // opens a hole in the meatball centers
    MEAT_MODE_SPOT,       // draws the meatball in one color w/ strength as diameter
    MEAT_MODE_RIPPLE,     // "the talented Meatball Ripplely"
    MEAT_MODE_DITHER,     // old-school dithering feel
    MEAT_MODE_DIAMOND,    // diamond balls... is that a thing?
    MEAT_MODE_RICO,       // His name was Rico.  He wore a...
    MEAT_MODE_CNT         // how many modes... must be last
} meat_mode;

/**
 * These values determine how each ball moves around the screen,
 * relative to the center of the screen... cx, cy.
 * Essentially, x and y will change with time, t, in functions
 * of the following form (using x as an example)...
 * x = cx + a * sinf((t * b) + c) + d
 */
typedef struct {
    float a;
    float b;
    float c;
    float d;
} move_data;


typedef struct {
    float x;
    float y;
    float strength;
    move_data mx;
    move_data my;
} meatball;

const int ball_cnt = 12;

int main() {
    srand((unsigned)time(NULL));

    /**
     * This gives each ball one of the 6 fully saturated primary and
     * secondary colors on the RGB color wheel.  It uses 3-bit patterns
     * to determine color where each bit indicates whether the red,
     * green, and blue components of the color are off or fully on.
     * The bit patterns 000 (zero) and 111 (seven) are avoided
     * as they are black and white, respectively and feel colorless.
     */
    TPixel colors[ball_cnt];
    for(int i = 0; i < ball_cnt; i++) {
        unsigned color = i % 6 + 1;  // color is the bit pattern for 1--6
        unsigned char r = color & (1 << 2) ? 0xFF : 0x00;
        unsigned char g = color & (1 << 1) ? 0xFF : 0x00;
        unsigned char b = color & (1 << 0) ? 0xFF : 0x00;
        colors[i] = tigrRGB(r, g, b);
    }

    TPixel background_color = tigrRGB(0x55, 0xBB, 0x55);

    Tigr *screen = tigrWindow(300, 200, __FILE__, TIGR_FIXED);
    float cx = screen->w / 2.0;  // center X
    float cy = screen->h / 2.0;  // center Y

    /**
     * This value just needs to be something that increases every
     * frame.  Could just be a frame counter, but since time maps
     * to a clearer human perception, it produces a more consistent
     * "pace" when used in calculations, regardless of the speed
     * of the machine this is running on.
     */
    float t = 0;  // time since launch
    meatball balls[ball_cnt];

    /**
     * As a reminder, the movement of each ball's center is based
     * on math such as the following, which updates the x coordinate
     * of the center of the ball.
     * 
     * x = cx + a * [sin|cos]((t * b) + c) + d
     */
    for(int i = 0; i < ball_cnt; i++) {
        meatball m = {
            .x = 0, .y = 0,  // any value in these is clobbered every frame
            .strength = rand() * 1.0 / RAND_MAX * 150 + 10.0,
            .mx = (move_data){
                .a = 100 * (rand() % 2 * 2 - 1),
                .b = rand() * 1.0 / RAND_MAX * 5.0 - 2.5,
                .c = rand() * 60.0 / RAND_MAX,
                .d = rand() * 1.0 / RAND_MAX * 40.0 - 20.0,
            },
            .my = (move_data){
                .a = 50 * (rand() % 2 * 2 - 1),
                .b = rand() * 1.0 / RAND_MAX * 6.0 - 3.0,
                .c = rand() * 60.0 / RAND_MAX,
                .d = rand() * 1.0 / RAND_MAX * 30.0 - 15.0,
            },
        };
        balls[i] = m;
    }

    float threshold = 0.6;

    meat_mode mode = MEAT_MODE_SOLID;
    while(!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {
        t += tigrTime() / 8.0;  // Move at 1/8th speed

        int key = tigrReadChar(screen);
        if(key == 'm' || key == 'M') {
            mode = (mode + 1) % MEAT_MODE_CNT;
        }

        /**
         * OK... One more time for posterity...
         * 
         * x = cx + a * [sin|cos]((t * b) + c) + d
         */
        for(int i = 0; i < ball_cnt; i++) {
            meatball *m = &balls[i];
            m->x = cx + m->mx.a * sinf(t * m->mx.b + m->mx.c) + m->mx.d;
            m->y = cy + m->my.a * sinf(t * m->my.b + m->my.c) + m->my.d;
        }

        /* Go through each pixel on the screen and color it */
        for(int y = 0; y < screen->h; y++) {
            for(int x = 0; x < screen->w; x++) {
                int i = y * screen->w + x;
                float sum_influence = 0.0;
                float max_influence = 0.0;
                int dominant_ball = -1;

                /**
                 * Find the dominant ball relative to this pixel by influence...
                 */
                for(int k = 0; k < ball_cnt; k++) {
                    float dx = x - balls[k].x;
                    float dy = y - balls[k].y;
                    float dist_sq = (dx * dx + dy * dy);

                    float influence = 0.0;
                    if(
                        (mode == MEAT_MODE_SOLID &&  dist_sq >= 0) ||
                        (mode == MEAT_MODE_HOLE    &&  dist_sq > (1.75 * balls[k].strength)) ||
                        (mode == MEAT_MODE_SPOT    &&  dist_sq < balls[k].strength) ||
                        (mode == MEAT_MODE_RIPPLE  && sinf(sqrtf(dist_sq)) < 0) ||
                        (mode == MEAT_MODE_DITHER  && cosf(powf(dist_sq, 1)) < 0.65) ||
                        (mode == MEAT_MODE_DIAMOND && (fabsf(dx) + fabsf(dy)) < powf(balls[k].strength, 0.65)) ||
                        (mode == MEAT_MODE_RICO    && sinf((fabsf(dx) + fabsf(dy))) < 0)
                      ) {
                        influence = powf(balls[k].strength, 2) / powf(dist_sq, 1.5);
                    }
                    
                    sum_influence += influence;
                    
                    if(influence > max_influence) {
                        max_influence = influence;
                        dominant_ball = k;
                    }
                }

                /**
                 * Color the pixel based on the dominant ball if it is
                 * influential enough.
                 */
                TPixel pix;
                
                if(sum_influence > threshold) {                    
                    TPixel base_color = colors[dominant_ball];

                    /* Normalize the influence for a smoother gradient */
                    float val = fminf(1.0, (sum_influence - threshold) * 2.5); 
                    pix.r = (unsigned char)(base_color.r * val);
                    pix.g = (unsigned char)(base_color.g * val);
                    pix.b = (unsigned char)(base_color.b * val);
                    pix.a = 0xff;
                } else {
                    /* This pixel is too isolated to be a ball color */
                    pix = background_color; 
                }

                screen->pix[i] = pix;
            }

            tigrPrint(screen, tfont, 3, 3, tigrRGB(0xFF, 0xFF, 0xFF), "'m' toggles mode");
        }

        tigrUpdate(screen);
    }

    tigrFree(screen);
    return 0;
}