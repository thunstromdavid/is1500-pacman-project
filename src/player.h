// Authored by David Thunström
// Date 2025-11-10

#ifndef PLAYER
#define PLAYER
#include "game.h"
#include "common.h"

typedef struct {
    // Pixel cords
    int px;
    int py;
    //Tile cords
    int tx;
    int ty;

    dir_t dir;
    dir_t req_dir; //Requested

    int score; // Might move this?
    int lives;
} player_t;


void player_init(player_t *p);
void player_handle_input(player_t *p, dir_t input_dir);
void player_update(player_t *p);
void player_render(player_t *p);
#endif
