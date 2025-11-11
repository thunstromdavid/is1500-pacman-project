// Authored by David Thunström and Mathias Jonasson
// Date 2025-11-11

#include <stdlib.h>
#include "game.h"
#include "player.h"
#include "gamemap.h"
#include "graphics.h"
#include "input.h"

player_t player;
game_state_t game_state;

void game_init(){
    game_state = GAME_STATE_INIT;
    player_init(&player);
    set_gamemap();
}

void game_update() {
    if(player.lives < 1){
        game_state = GAME_STATE_GAME_OVER;
    }
    set_gamemap();
    handle_input(&player);
    player_update(&player);
    player_render(&player);
}