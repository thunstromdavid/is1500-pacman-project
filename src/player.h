// Authored by David Thunström
// Date 2025-11-10

#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>

// Size of a tile in pixels
#define SIZE 8

void set_postition(int x, int y);

void move_up();

void move_down();

void move_left();

void move_right();

#endif
