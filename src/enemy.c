#include <stdlib.h>
#include "player.h"
#include "gamemap.h"
#include "common.h"

void enemy_init(enemy_t *e) {
    e -> tx = 20;
    e -> ty = 14;

    e -> px = tx * TILE_SIZE;
    e -> py = ty * TILE_SIZE;

    e -> dir = DIR_NONE;
    e -> req_dir = DIR_NONE;
}

void enemy_set_position(enemy_t *e, int px, int py) {
    e -> px = px;
    e -> py = py;
}

void state_mode_enemy(void) {
    
}

void move_enemy()