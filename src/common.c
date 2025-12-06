// Authored by Mathias Jonasson and David Thunström
// Date 2025-11-29

#include "common.h"
#include "gamemap.h"
#include "input.h"
#include "graphics.h"

void character_init(character_t *c, int tx, int ty, int colour) {
    c -> tx = tx;
    c -> ty = ty;

    c -> px = c -> tx * TILE_SIZE;
    c -> py = c -> ty * TILE_SIZE;

    c -> box.x = c -> px;
    c -> box.y = c -> py;

    c -> box.w = TILE_SIZE;
    c -> box.h = TILE_SIZE;

    c -> dir = DIR_UP;
    c -> req_dir = DIR_NONE;

    c -> colour = colour;
}

static unsigned int next_random = 1; 

// "Fake" Random function 
int get_random(int range) {
    next_random = next_random * 1103515245 + 12345;
    return (((unsigned int)(next_random / 65536) % 32768) + get_sw()) % range; // Add switch state to improve randomness
}

void dir_to_movement(dir_t dir, int *dx, int *dy) {
    *dx = 0;
    *dy = 0;
    switch (dir) {
        case DIR_UP:    
            *dy = -1;
            break;
        case DIR_DOWN:  
            *dy = 1;  
            break;
        case DIR_LEFT:  
            *dx = -1; 
            break;
        case DIR_RIGHT: 
            *dx = 1;  
            break;
        case DIR_NONE:
            break;
    }
}

// Remade to be able to check collision between character and rectangle (points or enenemy)
int check_rect_collision(Rect *r1, Rect *r2) {
    int left1   = r1->x;
    int right1  = r1->x + r1->w;
    int top1    = r1->y;
    int bottom1 = r1->y + r1->h;

    int left2   = r2->x;
    int right2  = r2->x + r2->w;
    int top2    = r2->y;
    int bottom2 = r2->y + r2->h;

    if (bottom1 <= top2) return 0;
    if (top1 >= bottom2) return 0;
    if (left1 >= right2) return 0;
    if (right1 <= left2) return 0;

    return 1;
}



int check_collision_entity(character_t *p, Rect *r) {
    if (check_rect_collision(&p->box, r)) {
        return 1;
    }
    return 0;
}

int check_collision_entities(character_t *player, character_t *enemies, int num_enemies) {
    for (int i = 0; i < num_enemies; i++) {
        if (check_collision_entity(player, &enemies[i].box)) {
            return 1;
        }
    }
    return 0;
}

int can_move_to(int tx, int ty){
    if (ty < 0 || ty >= MAP_HEIGHT){
        return 0;
    }
    if ((tx < 0 || tx >= MAP_WIDTH) || map[ty][tx] == OUTSIDE){
        if(ty == 14) {
            return 1;
        }
        return 0; 
    }
    return map[ty][tx] == PATH;
}

int is_centered(int val) {
    return (val % TILE_SIZE) == 0;
}

void update_entity_position(int *px, int *py, Rect *box, dir_t *current_dir, dir_t req_dir, int speed) {
    int rdx, rdy;
    // Try requested direction
    if (req_dir != DIR_NONE && req_dir != *current_dir) {
        if (is_centered(*px) && is_centered(*py)) {
            dir_to_movement(req_dir, &rdx, &rdy);
            int ntx = (*px / TILE_SIZE) + rdx;
            int nty = (*py / TILE_SIZE) + rdy;

            if (can_move_to(ntx, nty)) {
                *current_dir = req_dir;
            }
        }
    }

    // Move in current direction
    dir_to_movement(*current_dir, &rdx, &rdy);
    
    if (*current_dir != DIR_NONE) {
        int npx = *px + (rdx * speed);
        int npy = *py + (rdy * speed);

        int check_x = npx;
        int check_y = npy;
        
        if (rdx > 0) check_x = npx + TILE_SIZE - 1;
        if (rdy > 0) check_y = npy + TILE_SIZE - 1;
        
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
            box->x = npx;
            box->y = npy;
        } else {
            // Wall has been hit. ALiigns to grid
            *px = current_tx * TILE_SIZE;
            *py = current_ty * TILE_SIZE;
            *current_dir = DIR_NONE;

            box->x = *px;
            box->y = *py;
        }
    }
}

void remove_character(character_t *c) {
    draw_character(c->px, c->py, 0x00);
}