// Authored by David Thunström and Mathias Jonasson
// Date 2025-11-11

#include <stdlib.h>
#include "game.h"
#include "player.h"
#include "gamemap.h"
#include "graphics.h"
#include "input.h"
#include "common.h"
#include "timer.h"

player_t player;
game_state_t game_state;


void game_init(){
    game_state = GAME_STATE_INIT;
    player_init(&player);
    set_gamemap();
    timer_init(60); 
    player_render(&player);

}

void game_update() {
    if(player.lives < 1){
        game_state = GAME_STATE_GAME_OVER;
    }
    player_render(&player);
    handle_input(&player);
    player_update(&player);
}