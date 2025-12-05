// Authored by David Thunström
// Date 2025-11-10
#include "player.h"
#include "common.h"
#include "graphics.h"


void player_reset_pos(player_t *p){
    character_init(&p->base, 12, 14, PACMAN_COLOUR);
}

void player_init_stats(player_t *p) {
    p -> lives = 3;
    p -> score = 0;

    player_reset_pos(p);
}

void player_handle_input(player_t *p, dir_t input_dir){
    if(input_dir != DIR_NONE){
        p->base.req_dir = input_dir;
    }
}

void player_update(player_t *p){
    update_entity_position(&p->base.px, &p->base.py, &p->base.box, &p->base.dir, p->base.req_dir, 1);
    player_render(p);
}

void player_render(player_t *p){
    redraw_tile(p->base.px, p->base.py, p->base.dir);
    draw_character(p->base.px, p->base.py, p->base.colour); 
}