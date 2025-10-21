// Authored by David Thunström
// Date 2025-10-21

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>

// Resolution of the screen and pixel buffer
// https://canvas.kth.se/courses/56262/pages/literature-and-resources
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// Initialize VGA output
void vga_init();

// Set value of pixel at position x and y to 8 bit color
// Might change to 16 bit? Software resources unclear
void set_pixel(int x, int y, uint8_t color);

// Fill display
void fill_display(uint8_t color);

#endif
