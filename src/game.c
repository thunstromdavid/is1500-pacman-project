// Authored by David Thunström and Mathias Jonasson
// Date 2025-11-11

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
enemy_t enemy1 ,enemy2, enemy3, enemy4;
game_state_t game_state;

void game_init(){
    game_state = GAME_STATE_INIT;
    player_init(&player);
    enemy_init(&enemy1, 24, 18, 0xE0);
    enemy_init(&enemy2, 27, 15, 0xE4);
    enemy_init(&enemy3, 27, 21, 0xE5);
    enemy_init(&enemy4, 27, 8, 0xE9);
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
                enemy_render(&enemy1);
                enemy_render(&enemy2);
                enemy_render(&enemy3);
                enemy_render(&enemy4);
            }
            break;

        case GAME_STATE_RUNNING:
            
            handle_input(&player);

            //Enemy updates and rendering
            state_mode_enemy(&enemy1);
            state_mode_enemy(&enemy2);
            state_mode_enemy(&enemy3);
            state_mode_enemy(&enemy4);
            enemy_render(&enemy1);
            enemy_render(&enemy2);
            enemy_render(&enemy3);
            enemy_render(&enemy4);

            //Player update and rendering
            player_update(&player);
            player_render(&player);
            break;

        case GAME_STATE_GAME_OVER:
                break;
            
        default:
            break;
    }
    
}