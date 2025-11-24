// Authored by David Thunström and Mathias Jonasson
// Date 2025-11-11

#include <stdlib.h>
#include "game.h"
#include "player.h"
#include "gamemap.h"
#include "graphics.h"
#include "input.h"
#include "common.h"

player_t player;
game_state_t game_state;

void timer_start(void) {
    volatile int* timer = (volatile int*) 0x04000020;

    int update = 1000000; //30 hz

    timer[2] = update & 0xFFFF; 
    
    timer[3] = update >> 16; 
    
    timer[1] = (3 << 1); 
}

void game_init(){
    timer_start();
    game_state = GAME_STATE_INIT;
    player_init(&player);
    set_gamemap();
}

void game_update() {
    if(player.lives < 1){
        game_state = GAME_STATE_GAME_OVER;
    }
    player_render(&player);
    handle_input(&player);
    player_update(&player);
}