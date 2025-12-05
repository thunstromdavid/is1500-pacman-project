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
#include "screens.h"
#include "points.h"
#include "display.h"
//#include "measurement.h"
//#include "dtekv-lib.h"


// Define Global Variables
player_t player;
enemy_t enemies[NUM_ENEMIES];
game_state_t game_state;
point_t points[MAX_POINTS];

// Helper to reset all data for a fresh run
void reset_game_data() {
    player_init_stats(&player);
    player_reset_pos(&player);
    enemies_init(enemies);
    points_init(points);
    fill_display(0x00); 
    set_gamemap();      
}

void game_init(){
    game_state = GAME_STATE_INIT;
    player_init_stats(&player);
}

void game_update() {
    static int button_cooldown = 0;
    if (button_cooldown > 0) button_cooldown--;
    
    switch(game_state) {
        case GAME_STATE_INIT:
            draw_menu();
            
            // Check button HERE. If pressed, transition state.
            if (get_btn() && button_cooldown == 0) {
                reset_game_data(); // Reset stats/map
                game_state = GAME_STATE_RUNNING;
                button_cooldown = 30; // Wait 0.5 seconds (30 ticks)
            }
            break;

        case GAME_STATE_RUNNING:
            set_score_on_display(player.score);
            handle_input(&player);

            // Enemy Logic
            for (int i = 0; i < NUM_ENEMIES; i++) {
                if(check_collision_entity(&player.base, &enemies[i].base.box)) {
                    player.lives--;

                    if (player.lives <= 0) {
                        game_state = GAME_STATE_GAME_OVER;
                    } else {
                        remove_character(&player.base);
                        remove_enemies(enemies);
                        player_reset_pos(&player);
                        enemies_init(enemies);
                    }
                }
            }
            player.score += check_point_collision(&player.base.box, points);
            set_score_on_display(player.score);
            if (player.score >= MAX_POINTS * POINT_VALUE) {
                game_state = GAME_STATE_GAME_OVER;
            }
            if (get_btn() && button_cooldown == 0){
                game_state = GAME_STATE_PAUSE;
                button_cooldown = 30;
            }

            //Update object on screen
            point_render(points);
            enemies_update(enemies);
            player_update(&player);
            
            
            break;
        case GAME_STATE_PAUSE:
            draw_pause();
            if(get_btn() && button_cooldown == 0){
                game_state = GAME_STATE_RUNNING;
                button_cooldown = 30;
                fill_display(0x00); 
                set_gamemap();    
            }
            break;

        case GAME_STATE_GAME_OVER:
            if(player.score >= MAX_POINTS * POINT_VALUE) {
                draw_win();
            } else {
                draw_game_over();
            }
            if (get_btn() && button_cooldown == 0) {
                reset_game_data();
                game_state = GAME_STATE_RUNNING;
                button_cooldown = 30;
            }
            break;
        
            
        default:
            break;
    }
}

