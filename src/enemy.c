#include "enemy.h"
#include "gamemap.h"
#include "common.h"
#include "graphics.h"

void enemy_init(enemy_t *e) {
    e -> tx = 27;
    e -> ty = 14;

    e -> px = e -> tx * TILE_SIZE;
    e -> py = e -> ty * TILE_SIZE;

    e -> dir = DIR_UP;
    e -> req_dir = DIR_NONE;
}

void state_mode_enemy(enemy_t *e) {
    update_entity_position(&e->px, &e->py, &e->dir, e->req_dir, 1);
    
    if (e->dir == DIR_NONE) {
        e->dir = get_random(4);
    }
}


void enemy_render(enemy_t *e) {
    redraw_tile(e->px, e->py, e->dir);
    draw_character(e -> px, e -> py, 0xE0);
}