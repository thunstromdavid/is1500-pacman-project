// Authored by David Thunström
// Date 2025-10-21

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include "common.h"

// Resolution of the screen and pixel buffer
// https://canvas.kth.se/courses/56262/pages/literature-and-resources
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define PACMAN_COLOUR 0xFC
#define COIN_COLOUR 0xFF

// Initialize VGA output
void vga_init(void);

// Set value of pixel at position x and y to 8 bit color
// Might change to 16 bit? Software resources unclear
void set_pixel(int x, int y, uint8_t color);

void draw_tile(int x, int y, int tile_type);

void draw_point(int x, int y);

void draw_character(int x, int y, uint8_t colour);

void redraw_tile(int old_x, int old_y, dir_t direction);

// Fill display
void fill_display(uint8_t color);

#endif