// Authored by David Thunström
// Date 2025-11-10

#include <stdlib.h>
#include "player.h"
#include "gamemap.h"
#include "common.h"

void player_init(player_t *p){
    p -> tx = 12;
    p -> ty = 14;   

    p -> px = p -> tx * TILE_SIZE;
    p -> py = p -> ty * TILE_SIZE;

    p -> dir = DIR_NONE;
    p -> req_dir = DIR_NONE;

    p -> score = 0;
    p -> lives = 3; 
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

//REMOVE MAYBE?
void player_set_position(player_t *p, int px, int py){
    p->px = px;
    p->py = py;
}

void player_handle_input(player_t *p, dir_t input_dir){
    if(input_dir != DIR_NONE){
        p -> req_dir = input_dir;
    }

}

int is_centered(int val) {
    return (val % TILE_SIZE) == 0;
}

void player_update(player_t *p){
    // Try requested direction
    if(p->req_dir != DIR_NONE && p->req_dir != p->dir){

        if ((is_centered(p->px) && is_centered(p->py)) && (p->px > 0 && p->px < SCREEN_WIDTH)) {
            int rdx, rdy;
            dir_to_movement(p->req_dir, &rdx, &rdy);
            int npx = (p->px / TILE_SIZE) + rdx;
            int npy = (p->py / TILE_SIZE) + rdy;

            int ntx = npx / TILE_SIZE;
            int nty = npy / TILE_SIZE;

            if(can_move_to(npx, npy)){
                p->dir = p->req_dir;
            }
        }
    }

    //Move in current direction
    int dx, dy;
    dir_to_movement(p->dir, &dx, &dy);
    if(p->dir != DIR_NONE){
        int npx = p->px + dx;
        int npy = p->py + dy;

        int check_x = npx;
        int check_y = npy;
        
        if (dx > 0) check_x = npx + TILE_SIZE - 1;
        if (dy > 0) check_y = npy + TILE_SIZE - 1;
        
        int ntx = check_x / TILE_SIZE;
        int nty = check_y / TILE_SIZE;

        int current_x = p->px / TILE_SIZE;
        int current_y = p->py / TILE_SIZE;
        
        if((ntx == current_x && nty == current_y) || can_move_to(ntx, nty)){
            if (npx < - TILE_SIZE) {
                npx = SCREEN_WIDTH - TILE_SIZE;
            }
            if (npx > SCREEN_WIDTH) {
                npx = -TILE_SIZE + 1;
            }
            p->px = npx;
            p->py = npy;
            player_set_position(p, npx, npy);
        }
        else{
            p->dir = DIR_NONE;
        }
    }
}

void player_render(player_t *p){
    redraw_tile(p->px, p->py, p->dir);
    draw_player(p->px, p->py); 
}