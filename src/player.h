// Authored by David Thunström
// Date 2025-11-10

#ifndef PLAYER_H
#define PLAYER_H


void player_set_position(int tile_x, int tile_y);

// Movement based on tiles
void move_up(void);
void move_down(void);
void move_left(void);
void move_right(void);

// Draw player at current position
void player_render(void);

#endif
