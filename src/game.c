// Authored by David Thunström and Mathias Jonasson
// Date 2025-11-11

#include <stdlib.h>
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "gamemap.h"
#include "graphics.h"
#include "input.h"
#include "common.h"
#include "timer.h"

player_t player;
enemy_t enemy;
game_state_t game_state;

void game_init(){
    timer_init(60); 
    game_state = GAME_STATE_INIT;
    player_init(&player);
    enemy_init(&enemy);
    set_gamemap();
}

void game_update() {
    if(player.lives < 1){
        game_state = GAME_STATE_GAME_OVER;
    }
    handle_input(&player);
    state_mode_enemy(&enemy);
    enemy_render(&enemy);
    player_update(&player);
    player_render(&player);
}