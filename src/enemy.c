#include "enemy.h"
#include "common.h"
#include "graphics.h"

void enemy_init(enemy_t *e, int posx, int posy, int colour) {
    character_init(&e->base, posx, posy, colour);
}

void state_mode_enemy(enemy_t *e) {
    update_entity_position(&e->base.px, &e->base.py, &e->base.dir, e->base.req_dir, 1);
    
    int new_dir = get_random(4);

    if ((e->base.dir % 2 == 0 && new_dir != e->base.dir + 1) || (e->base.dir % 2 == 1 && new_dir != e->base.dir - 1)) {
        e->base.req_dir = new_dir;
    }
    if (e->base.dir == DIR_NONE ) {
        e->base.dir = get_random(4);
    }
}


void enemy_render(enemy_t *e) {
    redraw_tile(e->base.px, e->base.py, e->base.dir);
    draw_character(e->base.px, e->base.py, e->base.colour);
}