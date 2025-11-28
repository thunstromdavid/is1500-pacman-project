#include "points.h"
#include "gamemap.h"
#include "graphics.h"
#include "common.h"

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

            if (map[y][x] == PATH && (get_random(100) % 100) < 30) { // Randomly place points
                points[count].tx = x;
                points[count].ty = y;
                
                // Center the point in the tile
                points[count].px = (x * TILE_SIZE) + (3 * TILE_SIZE / 8);
                points[count].py = (y * TILE_SIZE) + (3 * TILE_SIZE / 8);
                
                points[count].box.x = points[count].px;
                points[count].box.y = points[count].py;
                points[count].box.w = TILE_SIZE / 4;
                points[count].box.h = TILE_SIZE / 4;

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

int check_point_collision(Rect *box, point_t *points) {
    for (int i = 0; i < MAX_POINTS; i++) {
        if (points[i].active) {
            if (check_rect_collision(box, &points[i].box)) {
                points[i].active = 0;
                return POINT_VALUE;
            }
        }
    }
    return 0;
}               
 