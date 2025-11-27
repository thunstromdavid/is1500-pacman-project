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

void enemy_set_position(enemy_t *e, int px, int py) {
    e -> px = px;
    e -> py = py;
}

void state_mode_enemy(enemy_t *e) {

    int dx, dy;
    dir_to_movement(e -> dir, &dx, &dy);
    int npx = e -> px + dx;
    int npy = e -> py + dy;

    int check_x = npx;
    int check_y = npy;
        
    if (dx > 0) check_x = npx + TILE_SIZE - 1;
    if (dy > 0) check_y = npy + TILE_SIZE - 1;

    int ntx = check_x / TILE_SIZE;
    int nty = check_y / TILE_SIZE;

    int current_tx = e -> px / TILE_SIZE;
    int current_ty = e -> py / TILE_SIZE;

    if((current_tx == ntx && current_ty == nty) || can_move_to(ntx, nty)) {
        e->px = npx;
        e->py = npy;
        enemy_set_position(e, npx, npy);
    } else {
        e -> dir = get_random(4);    
    }
}


void enemy_render(enemy_t *e) {
    redraw_tile(e->px, e->py, e->dir);
    draw_character(e -> px, e -> py, 0xE0);
}