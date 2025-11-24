// Authored by Mathias Jonasson
// Date 2025-10-21

#include "graphics.h"
#include "gamemap.h"
#include "common.h"


// Pointer to the VGA Screen Buffer
volatile uint8_t* vga_buffer = (volatile uint8_t*) 0x08000000;

// Initialize VGA output by filling the screen with a color
void vga_init(){
    fill_display(0x00);
}

// Set value of pixel at position x and y to 8 bit color
void set_pixel(int x, int y, uint8_t color) {
    vga_buffer[y * SCREEN_WIDTH + x] = color;
}

void draw_tile(int x, int y, int tile_type){
    int startX = x * TILE_SIZE;
    int startY = y * TILE_SIZE;
    int endX = startX + TILE_SIZE;
    int endY = startY + TILE_SIZE;

    switch (tile_type) {
        case PATH:
            for (int y = startY; y < endY; y++) {
                for (int x = startX; x < endX; x++) {
                    set_pixel(x, y, 0x00);
                }
            }
        break;

        case WALL_VERTICAL:
            for (int y = startY; y < endY; y++) {
                for (int x = startX + TILE_SIZE / 2 - 1; x <= startX + TILE_SIZE / 2 + 1; x++) {
                    set_pixel(x, y, 0x1F);
                }
            }
        break;
        
        case WALL_HORIZONTAL:
            for (int y = startY + TILE_SIZE / 2 - 1; y <= startY + TILE_SIZE / 2 + 1; y++){
                for (int x = startX; x < endX; x++) {
                    set_pixel(x, y, 0x1F);
                }
            }
        break;

        case WALL_CORNER_TL:
            for (int y = startY + TILE_SIZE / 2 - 1; y <= startY + TILE_SIZE / 2 + 1; y++) {
                for (int x = startX + TILE_SIZE / 2 - 1; x <= endX; x++) {
                    set_pixel(x, y, 0x1F);
                }
            }    
            for (int y = startY + TILE_SIZE / 2 + 1; y <= endY; y++) {
                for (int x = startX + TILE_SIZE / 2 - 1; x <= startX + TILE_SIZE / 2 + 1; x++) {
                    set_pixel(x, y, 0x1F);
                }
            }
        break;

        case WALL_CORNER_TR:
            for (int y = startY + TILE_SIZE / 2 - 1; y <= startY + TILE_SIZE / 2 + 1; y++) {
                for (int x = startX; x <= startX + TILE_SIZE / 2 + 1; x++) {
                    set_pixel(x, y, 0x1F);
                }
            }    
            for (int y = startY + TILE_SIZE / 2 + 1; y <= endY; y++) {
                for (int x = startX + TILE_SIZE / 2 - 1; x <= startX + TILE_SIZE / 2 + 1; x++) {
                    set_pixel(x, y, 0x1F);
                }
            }
        break;

        case WALL_CORNER_BL:
            for (int y = startY + TILE_SIZE / 2 - 1; y <= startY + TILE_SIZE / 2 + 1; y++) {
                for (int x = startX + TILE_SIZE / 2 - 1; x <= endX; x++) {
                    set_pixel(x, y, 0x1F);
                }
            for (int y = startY; y <= startY + TILE_SIZE / 2 + 1; y++) {
                for (int x = startX + TILE_SIZE / 2 - 1; x <= startX + TILE_SIZE / 2 + 1; x++) {
                    set_pixel(x, y, 0x1F);
                }
            }
        }
        break;

        case WALL_CORNER_BR:
            for (int y = startY + TILE_SIZE / 2 - 1; y <= startY + TILE_SIZE / 2 + 1; y++) {
                for (int x = startX; x <= startX + TILE_SIZE / 2 + 1; x++) {
                    set_pixel(x, y, 0x1F);
                }
            }    
            for (int y = startY; y <= startY + TILE_SIZE / 2 + 1; y++) {
                for (int x = startX + TILE_SIZE / 2 - 1; x <= startX + TILE_SIZE / 2 + 1; x++) {
                    set_pixel(x, y, 0x1F);
                }
            }
        break;
    }
}

void draw_player(int x, int y) {
    int startX = x;
    int startY = y;

    int endX = startX + TILE_SIZE;
    int endY = startY + TILE_SIZE;

    if (endX > SCREEN_WIDTH) endX = SCREEN_WIDTH;
    if (endY > SCREEN_HEIGHT) endY = SCREEN_HEIGHT;

    for (int y = startY; y < endY; y++) {
        for (int x = startX; x < endX; x++) {
            set_pixel(x, y, 0xFC);
        }
    }
}


// Fill display with a specific color
void fill_display(uint8_t color) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            vga_buffer[y * SCREEN_WIDTH + x] = color;
        }
    }
}