#include "enemy.h"
#include "common.h"
#include "graphics.h"

void enemy_init(enemy_t *e, int posx, int posy, int colour) {
    character_init(&e->base, posx, posy, colour);
}

void state_mode_enemy(enemy_t *e) {
    update_entity_position(&e->base.px, &e->base.py, &e->base.box, &e->base.dir, e->base.req_dir, 1);
    
    //Looking if a turn is possible
    int new_dir = get_random(4);
    int opposite = (e->base.dir == DIR_NONE) ? - 10 : (e->base.dir ^ 1) ; //Bitwise XOR, Up(00) will become Down(01), Left(10) --> Right(11). If DIR_NONE then it can go anywhere

    if (new_dir != opposite) {
        e->base.req_dir = new_dir;
    }
}


void enemy_render(enemy_t *e) {
    redraw_tile(e->base.px, e->base.py, e->base.dir);
    draw_character(e->base.px, e->base.py, e->base.colour);
}