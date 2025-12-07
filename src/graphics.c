// Authored by Mathias Jonasson and David Thunström
// Date 2025-12-05

#include "graphics.h"
#include "gamemap.h"
#include "common.h"
#include "screens.h"

// Pointer to the VGA Screen Buffer
volatile char* vga_buffer = (volatile char*) 0x08000000;

void vga_init(){
    fill_display(0x00);
}

void set_pixel(int x, int y, char colour) {
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) return;

    vga_buffer[y * SCREEN_WIDTH + x] = colour;
}

void fill_rect(int start_x, int start_y, int end_x, int end_y, char colour) {
    for (int y = start_y; y <= end_y; y++) {
        for (int x = start_x; x <= end_x; x++) {
            set_pixel(x, y, colour);
        }
    }
}

void draw_square(int x, int y, int size, char colour) {
    int end_x = x + size;
    int end_y = y + size;

    if (end_x > SCREEN_WIDTH) end_x = SCREEN_WIDTH;
    if (end_y > SCREEN_HEIGHT) end_y = SCREEN_HEIGHT;

    fill_rect(x, y, end_x, end_y, colour);
}


// Here we need to draw different tile types based on the tile_type parameter
void draw_tile(int x, int y, int tile_type){
    int start_x = x * TILE_SIZE;
    int start_y = y * TILE_SIZE;
    int end_x = start_x + TILE_SIZE;
    int end_y = start_y + TILE_SIZE;
    int middle_x = start_x + TILE_SIZE / 2;
    int middle_y = start_y + TILE_SIZE / 2;

    switch (tile_type) {
        case PATH:
            fill_rect(start_x, start_y, end_x, end_y, PATH_COLOUR);    
        break;

        case WALL_VERTICAL:
            fill_rect(middle_x- 1, start_y, middle_x + 1, end_y, WALL_COLOUR);
        break;
        
        case WALL_HORIZONTAL:
            fill_rect(start_x, middle_y - 1, end_x, middle_y + 1, WALL_COLOUR);
        break;

        case WALL_CORNER_TL:
            fill_rect(middle_x - 1, middle_y - 1, end_x, middle_y + 1, WALL_COLOUR);  
            fill_rect(middle_x - 1, middle_y + 1, middle_x + 1, end_y, WALL_COLOUR);
        break;

        case WALL_CORNER_TR:
            fill_rect(start_x, middle_y - 1, middle_x + 1, middle_y + 1, WALL_COLOUR);
            fill_rect(middle_x - 1, middle_y + 1, middle_x + 1, end_y, WALL_COLOUR);
        break;

        case WALL_CORNER_BL:
            fill_rect(middle_x - 1, middle_y - 1, end_x, middle_y + 1, WALL_COLOUR);
            fill_rect(middle_x - 1, start_y, middle_x + 1, middle_y + 1, WALL_COLOUR);
        break;

        case WALL_CORNER_BR:
            fill_rect(start_x, middle_y - 1, middle_x + 1, middle_y + 1, WALL_COLOUR);
            fill_rect(middle_x - 1, start_y, middle_x + 1, middle_y + 1, WALL_COLOUR);
        break;

        case OUTSIDE:
            fill_rect(start_x, start_y, end_x, end_y, PATH_COLOUR);    
        break;
        
    }
}

void draw_point(int x, int y){
    draw_square(x, y, TILE_SIZE / 4, POINT_COLOUR);
}

void draw_character(int x, int y, char colour) {
    draw_square(x, y, TILE_SIZE, colour);
}

// If we only update the pixels of the character, a tail will appear behind it. This function clears that tail.
void clear_tail(int px, int py, dir_t direction) {
    switch(direction)  {
        case DIR_UP:
            fill_rect(px, py + TILE_SIZE, px + TILE_SIZE, py + TILE_SIZE + 1, PATH_COLOUR);
            break;
            
        case DIR_DOWN:
            fill_rect(px, py - 1, px + TILE_SIZE, py, PATH_COLOUR);
            break;
            
        case DIR_LEFT:
            fill_rect(px + TILE_SIZE, py, px + TILE_SIZE + 1, py + TILE_SIZE, PATH_COLOUR);
            break;
            
        case DIR_RIGHT:
            fill_rect(px - 1, py, px, py + TILE_SIZE, PATH_COLOUR);
            break;
        default:
            break;
    }
}

// Checks if the difference is too big and clears the old position
void handle_screen_wrap(int old_x, int old_y, int new_x, int new_y) {
    if (get_diff(new_x, old_x) > TILE_SIZE || get_diff(new_y, old_y) > TILE_SIZE) {
        draw_character(old_x, old_y, 0x00); 
    }
}

// Fill display with a specific color
void fill_display(char colour) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            vga_buffer[y * SCREEN_WIDTH + x] = colour;
        }
    }
}

// Draw the full screen images. This one is used for the pixel arrays to draw screens like start screen, pause screen, game over screen etc.
void draw_full_screen(char* pixel_array) {
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        vga_buffer[i] = pixel_array[i];
    }
}