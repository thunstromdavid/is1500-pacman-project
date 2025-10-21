// Authored by Mathias Jonasson
// Date 2025-10-21

#include "graphics.h"

volatile int* vga_buffer = (volatile int*) 0x08000000;

void vga_init(){
    fill_display(0x00000000);
}

void set_pixel(int x, int y, uint8_t color) {
    vga_buffer[y * SCREEN_WIDTH + x] = color;
}

void fill_display(uint8_t color) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            vga_buffer[y * SCREEN_WIDTH + x] = color;
        }
    }
}