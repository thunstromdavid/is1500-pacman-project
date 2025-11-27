#include "startscreen.h"
#include "graphics.h"

void draw_start_screen(void) {
    fill_display(0x03);

    for(int y = 100; y < 140; y++) {
        for(int x = 120; x < 200; x++) {
            set_pixel(x, y, 0xFF);
        }
    }
}