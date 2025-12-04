#ifndef ENEMY
#define ENEMY
#include "game.h"
#include "common.h"

#define NUM_ENEMIES 4

typedef struct {
    character_t base;
} enemy_t;


void enemies_reset_pos(enemy_t *e);
void enemies_init(enemy_t *e);
void enemy_init(enemy_t *e, int posx, int posy, int colour);
void state_mode_enemy(enemy_t *e);
void enemy_render(enemy_t *e);
void enemies_render(enemy_t *enemies_array);
#endif