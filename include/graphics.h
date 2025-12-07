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
#define WALL_COLOUR 0x1F
#define PATH_COLOUR 0x00

void vga_init(void);

void draw_tile(int x, int y, int tile_type);

void draw_point(int x, int y);

void draw_character(int x, int y, char colour);

void handle_screen_wrap(int old_x, int old_y, int new_x, int new_y);

void clear_tail(int old_x, int old_y, dir_t direction);

void fill_display(char color);

void draw_full_screen(char* pixel_array);

#endif