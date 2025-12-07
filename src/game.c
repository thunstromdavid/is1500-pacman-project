// Authored by Mathias Jonasson David Thunström
// Date 2025-12-05

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


player_t player;
enemy_t enemies[NUM_ENEMIES];
game_state_t game_state;
point_t points[MAX_POINTS];
int button_cooldown = 0; 

static void reset_game_data() {
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

static int button_active() {
    return (get_btn() && button_cooldown == 0);
}

void game_update() {

    if (button_cooldown > 0) button_cooldown--;
    
    switch(game_state) {
        case GAME_STATE_INIT:
            draw_full_screen(START_SCREEN);
            
            if (button_active()) {
                reset_game_data(); 
                game_state = GAME_STATE_RUNNING;
                button_cooldown = 30; // Wait 0.5 seconds (30 ticks)
            }
            break;

        case GAME_STATE_RUNNING:
            set_score_on_display(player.score);
            handle_input(&player);

            // Enemy logic 
            if(check_collision_with_enemies(&player.base, enemies, NUM_ENEMIES)) {
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

            // Points logic
            player.score += check_point_collision(&player.base.box, points);
            set_score_on_display(player.score);
            if (player.score >= MAX_POINTS * POINT_VALUE) {
                game_state = GAME_STATE_GAME_OVER;
            }
            if (button_active()){
                game_state = GAME_STATE_PAUSE;
                button_cooldown = 30;
            }

            //Update object on screen
            point_render(points);
            enemies_update(enemies);
            player_update(&player);
            break;

        case GAME_STATE_PAUSE:
            draw_full_screen(PAUSE_SCREEN);
            if(button_active()){
                game_state = GAME_STATE_RUNNING;
                button_cooldown = 30;
                fill_display(0x00); 
                set_gamemap();    
            }
            break;

        case GAME_STATE_GAME_OVER:
            if(player.score >= MAX_POINTS * POINT_VALUE) {
                draw_full_screen(WIN_SCREEN);
            } else {
                draw_full_screen(GAME_OVER_SCREEN);
            }
            if (button_active()) {
                reset_game_data();
                game_state = GAME_STATE_RUNNING;
                button_cooldown = 30;
            }
            break;
        default:
            break;
    }
}