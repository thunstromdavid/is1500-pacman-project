#ifndef ENEMY
#define ENEMY
#include "game.h"
#include "common.h"

#define NUM_ENEMIES 4

typedef struct {
    character_t base;   
} enemy_t;

void enemies_init(enemy_t *enemies_array);
void enemies_update(enemy_t *enemies_array);
void remove_enemies(enemy_t *enemies_array);
#endif