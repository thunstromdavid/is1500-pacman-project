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
    if (tx >= MAP_WIDTH || ty >= MAP_HEIGHT){
        return 0;
    }
    return map[ty][tx] == PATH;
}

//REMOVE MAYBE?
void player_set_position(player_t *p, int tx, int ty){
    p->tx = tx;
    p->ty = ty;
}

void dir_to_movement(dir_t dir, int *dx, int *dy) {
    switch (dir) {
        case DIR_UP:    
            *dx = 0;  
            *dy = -1; 
            break;
        case DIR_DOWN:  
            *dx = 0;  
            *dy = 1; 
            break;
        case DIR_LEFT:  
            *dx = -1; 
            *dy = 0;  
            break;
        case DIR_RIGHT: 
            *dx = 1;  
            *dy = 0;  
            break;
        default:          
            *dx = 0;  
            *dy = 0; 
            break;
    }
}

void player_handle_input(player_t *p, dir_t input_dir){
    if(input_dir != DIR_NONE){
        p -> req_dir = input_dir;
    }

}

void player_update(player_t *p){
    // Try requested direction
    if(p->req_dir != DIR_NONE && p->req_dir != p->dir){
        int rdx, rdy;
        dir_to_movement(p->req_dir, &rdx, &rdy);
        int ntx = p->tx + rdx;
        int nty = p->ty + rdy;
        if(can_move_to(ntx, nty)){
            p->dir = p->req_dir;
        }
    }

    //Move in current direction
    int dx, dy;
    dir_to_movement(p->dir, &dx, &dy);
    if(p->dir != DIR_NONE){
        int ntx = p->tx + dx;
        int nty = p->ty + dy;
        
        if(can_move_to(ntx, nty)){
            p->tx = ntx;
            p->ty = nty;
            player_set_position(p, ntx, nty);
        }
        else{
            p->dir = DIR_NONE;
        }
    }
}

void player_render(player_t *p){
    draw_player(p->tx, p->ty);
}