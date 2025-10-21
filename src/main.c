#include <stdlib.h>
#include "graphics.h"

int main() {
    vga_init();

    for (int x = 100; x < 200; x++) {
        for (int y = 100; y < 200; y++) {
            set_pixel(x, y, 0x0000FF00);
        }
    }

    while (1) {

    }
}