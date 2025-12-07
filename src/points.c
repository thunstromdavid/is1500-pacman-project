// Authored by Mathias Jonasson and David Thunström
// Date 2025-12-05

#include "points.h"
#include "gamemap.h"
#include "graphics.h"
#include "common.h"

void points_init(point_t *points) {
    int count = 0;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
        
            if (map[y][x] == PATH) {
                
                // Center the point in the tile
                int px = (x * TILE_SIZE) + (3 * TILE_SIZE / 8);
                int py = (y * TILE_SIZE) + (3 * TILE_SIZE / 8);
                
                points[count].box.x = px;
                points[count].box.y = py;
                points[count].box.w = TILE_SIZE / 4;
                points[count].box.h = TILE_SIZE / 4;

                points[count].active = 1;
                count++;
            }
        }
    }
}

// Render all active points on the screen
void point_render(point_t *points){
    for(int i = 0; i < MAX_POINTS; i++){
        if(points[i].active){
            draw_point(points[i].box.x, points[i].box.y);
        }
    }
}

// We deactivate a point when the player collides with it and return the point value
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