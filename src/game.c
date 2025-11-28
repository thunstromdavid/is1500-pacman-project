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

player_t player;
enemy_t enemy1 ,enemy2, enemy3, enemy4;
game_state_t game_state;
point_t points[MAX_POINTS];
int score;

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
                enemy_render(&enemy1);
                enemy_render(&enemy2);
                enemy_render(&enemy3);
                enemy_render(&enemy4);
            }
            break;

        case GAME_STATE_RUNNING:
            
            //Handle player input
            handle_input(&player);

            // Check for collisions between player and enemies
            if (check_collision_entity(&player.base, &enemy1.base.box) ||
                check_collision_entity(&player.base, &enemy2.base.box) ||
                check_collision_entity(&player.base, &enemy3.base.box) ||
                check_collision_entity(&player.base, &enemy4.base.box)) {
                player.lives--;

                if (player.lives <= 0) {
                    game_state = GAME_STATE_GAME_OVER;
                }


                // Set new positions maybe? 
                remove_character(player.base.px, player.base.py);
                remove_character(enemy1.base.px, enemy1.base.py);
                remove_character(enemy2.base.px, enemy2.base.py);
                remove_character(enemy3.base.px, enemy3.base.py);
                remove_character(enemy4.base.px, enemy4.base.py);

                player_reset_pos(&player);
                enemy_init(&enemy1, 24, 18, 0xE0);
                enemy_init(&enemy2, 27, 15, 0xE4);
                enemy_init(&enemy3, 27, 21, 0xE5);
                enemy_init(&enemy4, 27, 8, 0xE9);
            }
            
            // Check for point collection and update score
           
            score += check_point_collision(&player.base.box, points);

            point_render(points);


            //Enemy updates and rendering¨
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