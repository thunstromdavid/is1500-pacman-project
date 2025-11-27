#ifndef ENEMY
#define ENEMY
#include "game.h"
#include "common.h"

typedef struct {
    int px;
    int py;
    
    int tx;
    int ty;

    dir_t dir;
    dir_t req_dir; 

    int colour;
} enemy_t;

void enemy_init(enemy_t *e, int posx, int posy, int colour);
void state_mode_enemy(enemy_t *e);
void enemy_render(enemy_t *e);
#endif