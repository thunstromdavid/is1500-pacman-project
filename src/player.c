#include <stdlib.h>
#include "gamemap.h"

int player_x = 0;
int player_y = 0;

// Check if the tile we want to move to is valid, not a wall
int can_move_to(int tile_x, int tile_y){
    if (tile_x >= MAP_WIDTH || tile_y >= MAP_HEIGHT){return 0;}
    
    return map[tile_y][tile_x] == PATH;
}

// Attempt to move, fails if not valid
void attempt_move(int dx, int dy){
    int new_x = player_x + dx;
    int new_y = player_y + dy;

    if(!(can_move_to(new_x, new_y))){return;}
    player_x = new_x;
    player_y = new_y;
}

// Teleport player to a valid position. Set starting postition
void player_set_position(int tile_x, int tile_y){
    if (can_move_to(tile_x, tile_y)){
        player_x = tile_x;
        player_y = tile_y;
    }
}


void move_up(void){player_y += 1;}
void move_down(void){player_y -= 1;}
void move_right(void){player_x += 1;}
void move_left(void){player_x -= 1;}

void player_render(void){
    draw_player(player_x, player_y);
}