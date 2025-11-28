#include "points.h"
#include "gamemap.h"
#include "graphics.h"


void points_init(point_t *points) {
    int count = 0;

    // Initialize all points to inactive first
    for (int i = 0; i < MAX_POINTS; i++) {
        points[i].active = 0;
    }

    // Loop through the map to find spots for dots
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            
            if (count >= MAX_POINTS) return;

            if (map[y][x] == PATH) {
                points[count].tx = x;
                points[count].ty = y;
                
                points[count].px = (x * TILE_SIZE) + (TILE_SIZE / 2);
                points[count].py = (y * TILE_SIZE) + (TILE_SIZE / 2);
                
                points[count].active = 1;
                count++;
            }
        }
    }
}

void point_render(point_t *points){
    for(int i = 0; i < MAX_POINTS; i++){
        if(points[i].active){
            draw_point(points[i].px, points[i].py);
        }
    }
}