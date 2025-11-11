// Authored by David Thunström
// Date 2025-11-10

#include <stdlib.h>
#include "player.h"
#include "gamemap.h"
#include "common.h"

void player_init(player_t *p){
    p -> tx = 1;
    p -> ty = 1;

    p -> px = p -> tx * TILE_SIZE;
    p -> py = p -> ty * TILE_SIZE;

    p -> dir = DIR_NONE;
    p -> req_dir = DIR_NONE;

    p -> score = 0;
    p -> lives = 3; 
}

void player_handle_input(player_t *p, dir_t input_dir){
    if(input_dir != DIR_NONE){
        p -> req_dir = input_dir;
    }
}

void player_update(player_t *p){
    
}