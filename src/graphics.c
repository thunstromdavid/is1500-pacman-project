// Authored by Mathias Jonasson
// Date 2025-10-21

#include "graphics.h"

// Pointer to the VGA Screen Buffer
volatile uint8_t* vga_buffer = (volatile uint8_t*) 0x08000000;

// Initialize VGA output by filling the screen with a color
void vga_init(){
    fill_display(0x0F);
}

// Set value of pixel at position x and y to 8 bit color
void set_pixel(int x, int y, uint8_t color) {
    vga_buffer[y * SCREEN_WIDTH + x] = color;
}

// Fill display with a specific color
void fill_display(uint8_t color) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            vga_buffer[y * SCREEN_WIDTH + x] = color;
        }
    }
}