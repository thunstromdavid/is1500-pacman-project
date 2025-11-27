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
#include "startscreen.h"

player_t player;
enemy_t enemy;
game_state_t game_state;

void game_init(){
    game_state = GAME_STATE_INIT;
    player_init(&player);
    enemy_init(&enemy);
    set_gamemap();
    timer_init(60); 
}

void game_update() {
    switch(game_state) {
        case GAME_STATE_INIT:
            draw_start_screen();
            // Check for any button press to start
            if (get_sw()) {
                game_state = GAME_STATE_RUNNING;
                fill_display(0x00); // Clear screen
                set_gamemap();     
                player_render(&player);
            }
            break;

        case GAME_STATE_RUNNING:
            if(player.lives < 1){
                game_state = GAME_STATE_GAME_OVER;
            }
            handle_input(&player);
            state_mode_enemy(&enemy);
            enemy_render(&enemy);
            player_update(&player);
            player_render(&player);
            break;

        case GAME_STATE_GAME_OVER:
                break;
            
        default:
            break;
    }
    
}