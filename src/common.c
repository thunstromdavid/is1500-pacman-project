#include "common.h"
#include "gamemap.h"
#include "input.h"

static unsigned int next_random = 1; 

// "Fake" Random function 
int get_random(int range) {
    next_random = next_random * 1103515245 + 12345;
    return (((unsigned int)(next_random / 65536) % 32768) + get_sw()) % range; // Add switch state to improve randomness
}

void dir_to_movement(dir_t dir, int *px, int *py) {
    switch (dir) {
        case DIR_UP:    
            *px = 0;  
            *py = -1; 
            break;
        case DIR_DOWN:  
            *px = 0;  
            *py = 1; 
            break;
        case DIR_LEFT:  
            *px = -1; 
            *py = 0;  
            break;
        case DIR_RIGHT: 
            *px = 1;  
            *py = 0;  
            break;
        default:          
            *px = 0;  
            *py = 0; 
            break;
    }
}    
int can_move_to(int tx, int ty){
    if (ty < 0 || ty >= MAP_HEIGHT){
        return 0;
    }
    if ((tx < 0 || tx >= MAP_WIDTH) && ty == 14){
        return 1; 
    }
    return map[ty][tx] == PATH;
}

int is_centered(int val) {
    return (val % TILE_SIZE) == 0;
}

void update_entity_position(int *px, int *py, dir_t *current_dir, dir_t req_dir, int speed) {
    // Try requested direction
    if (req_dir != DIR_NONE && req_dir != *current_dir) {
        if (is_centered(*px) && is_centered(*py)) {
            int rdx, rdy;
            dir_to_movement(req_dir, &rdx, &rdy);
            int ntx = (*px / TILE_SIZE) + rdx;
            int nty = (*py / TILE_SIZE) + rdy;

            if (can_move_to(ntx, nty)) {
                *current_dir = req_dir;
            }
        }
    }

    // Move in current direction
    int dx, dy;
    dir_to_movement(*current_dir, &dx, &dy);
    
    if (*current_dir != DIR_NONE) {
        int npx = *px + (dx * speed);
        int npy = *py + (dy * speed);

        int check_x = npx;
        int check_y = npy;
        
        if (dx > 0) check_x = npx + TILE_SIZE - 1;
        if (dy > 0) check_y = npy + TILE_SIZE - 1;
        
        int ntx = check_x / TILE_SIZE;
        int nty = check_y / TILE_SIZE;

        int current_tx = *px / TILE_SIZE;
        int current_ty = *py / TILE_SIZE;
        
        if ((ntx == current_tx && nty == current_ty) || can_move_to(ntx, nty)) {
            if (npx < -TILE_SIZE) {
                npx = SCREEN_WIDTH - TILE_SIZE;
            }
            if (npx > SCREEN_WIDTH) {
                npx = -TILE_SIZE + 1;
            }
            *px = npx;
            *py = npy;
        } else {
            // Wall has been hit. ALiigns to grid
            *px = current_tx * TILE_SIZE;
            *py = current_ty * TILE_SIZE;
            *current_dir = DIR_NONE;
        }
    }
}
