// Authored by David Thunström
// Date 2025-11-10

#ifndef PLAYER
#define PLAYER
#include "game.h"
#include "common.h"

typedef struct {
    character_t base;

    int score; 
    int lives;
} player_t;

void player_init_stats(player_t *p);
void player_reset_pos(player_t *p);
void player_handle_input(player_t *p, dir_t input_dir);
void player_update(player_t *p);
void player_render(player_t *p);
#endif
