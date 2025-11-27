// Authored by David Thunström
// Date 2025-11-10
#include "player.h"
#include "gamemap.h"
#include "common.h"
#include "graphics.h"

void player_init(player_t *p){
    character_init(&p->base, 12, 14, 0xFC);

    int lives = 3;
    int score = 0;
}

void player_handle_input(player_t *p, dir_t input_dir){
    if(input_dir != DIR_NONE){
        p -> base.req_dir = input_dir;
    }
}

void player_update(player_t *p){
    update_entity_position(&p->px, &p->py, &p->dir, p->req_dir, 1);
}

void player_render(player_t *p){
    redraw_tile(p->base.px, p->base.py, p->base.dir);
    draw_character(p->base.px, p->base.py, p->base.colour); 
}