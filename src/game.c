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


player_t player;
enemy_t enemies[NUM_ENEMIES];
game_state_t game_state;
point_t points[MAX_POINTS];
int score;

void game_init(){
    game_state = GAME_STATE_INIT;
    player_init_stats(&player);
    enemies_init(enemies);
    points_init(points);
    set_gamemap();
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
                point_render(points);
                player_render(&player);
                enemies_render(enemies);
            }
            break;

        case GAME_STATE_RUNNING:

            // TODO : ADD PAUSE FUNCTIONALITY
            // maybe check button press here to pause

            //Start displaying the score
            set_score_on_display(score);
            
            //Handle player input
            handle_input(&player);

            // Check for collisions between player and enemies
            if (check_collision_entities(&player.base, (character_t*)enemies, NUM_ENEMIES)) {
                player.lives--;

                if (player.lives <= 0) {
                    game_state = GAME_STATE_GAME_OVER;
                }


                player_reset_pos(&player);
                enemies_reset_pos(enemies);
            }
            
            // Call the function and save result
            score += check_point_collision(&player.base.box, points);

            
            // Check Game Over
            if (score == MAX_POINTS * POINT_VALUE) {
                game_state = GAME_STATE_GAME_OVER;
            }

            point_render(points);


            //Enemy updates and rendering¨
            enemies_render(enemies);


            //Player update and rendering
            player_update(&player);
            player_render(&player);
            break;

        case GAME_STATE_GAME_OVER:
            if(score == MAX_POINTS * POINT_VALUE) {
                draw_win();
            }
            else {
                draw_game_over();
            }
            break;
            
        default:
            break;
    }
    
}