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
#include "points.h"
#include "display.h"

player_t player;
enemy_t enemy1 ,enemy2, enemy3, enemy4;
game_state_t game_state;
point_t points[MAX_POINTS];
int score;
int score_left = MAX_POINTS;

void game_init(){
    game_state = GAME_STATE_INIT;
    player_init_stats(&player);
    enemy_init(&enemy1, 24, 18, 0xE0);
    enemy_init(&enemy2, 27, 15, 0xE4);
    enemy_init(&enemy3, 27, 21, 0xE5);
    enemy_init(&enemy4, 27, 8, 0xE9);
    points_init(points);
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
                point_render(points);
                player_render(&player);
                
            }
            break;

        case GAME_STATE_RUNNING:

            //Start displaying the score
            set_score_on_display(score);
            
            //Handle player input
            handle_input(&player);

           
            
            // Call the function and save result
            int points_gained = check_point_collision(&player.base.box, points);

            // Check if we actually hit something
            if (points_gained > 0) {
                score += points_gained; // Update score
                score_left--;           // Update remaining count
            }

            // 3. Check Game Over
            if (!score_left) {
                game_state = GAME_STATE_GAME_OVER;
            }

            point_render(points);


            //Enemy updates and rendering¨
            
            


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