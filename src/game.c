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
#include "measurement.h"
#include "dtekv-lib.h"

player_t player;
enemy_t enemies[NUM_ENEMIES];
game_state_t game_state;
point_t points[MAX_POINTS];
int score;
int stats_printed = 0;



void game_init(){
    game_state = GAME_STATE_INIT;
    player_init_stats(&player);
    enemies_init(enemies);
    points_init(points);
    timer_init(60); 
}
void game_update() {
 
    switch(game_state) {
        case GAME_STATE_INIT:
            draw_menu();
            // Check for any button press to start
            if (get_btn()) {
                game_state = GAME_STATE_RUNNING;
                fill_display(0x00); // Clear screen
                set_gamemap();  
                reset_timer();
                clear_counters();
            }
            break;

        case GAME_STATE_RUNNING:

        
            if(get_tick_count() == EXPECTED_TICKS){
                game_state = GAME_STATE_GAME_OVER;
            }

            set_score_on_display(score);
            
            handle_input(&player);

            for (int i = 0; i < NUM_ENEMIES; i++) {
                if(check_collision_entity(&player.base, &enemies[i].base.box)) {
                    //player.lives--;

                    if (player.lives <= 0) {
                        game_state = GAME_STATE_GAME_OVER;
                        read_and_print_counters();
                    }

                    remove_character(&player.base);
                    remove_enemies(enemies);
                    player_reset_pos(&player);
                    enemies_init(enemies);
                }
            }
            
            score += check_point_collision(&player.base.box, points);

            if (score == MAX_POINTS * POINT_VALUE) {
                game_state = GAME_STATE_GAME_OVER;
                read_and_print_counters();
            }

            point_render(points);
            enemies_update(enemies);
            player_update(&player);
            break;

        case GAME_STATE_GAME_OVER:
            
            if(score == MAX_POINTS * POINT_VALUE) {
                draw_win();
            }
            else {
                draw_game_over();
                
                if (stats_printed == 0) {
                    read_and_print_counters();
                    stats_printed = 1; // Mark as done
                }
            }
            break;
            
        default:
            break;
    }
    
}