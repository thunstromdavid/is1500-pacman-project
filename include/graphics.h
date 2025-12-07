// Authored by David Thunström
// Date 2025-10-21

#ifndef GRAPHICS
#define GRAPHICS

#include "common.h"

// Resolution of the screen and pixel buffer
// https://canvas.kth.se/courses/56262/pages/literature-and-resources
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define PACMAN_COLOUR 0xFC
#define POINT_COLOUR 0xFF

// Initialize VGA output
void vga_init(void);

// Set value of pixel at position x and y to 8 bit color
// Might change to 16 bit? Software resources unclear
void set_pixel(int x, int y, char color);

void draw_tile(int x, int y, int tile_type);

void draw_point(int x, int y);

void draw_character(int x, int y, char colour);

void redraw_tile(int old_x, int old_y, dir_t direction);

// Fill display
void fill_display(char color);

// Drawing the screens for the different game states
void draw_full_screen(char* pixel_array);

#endif