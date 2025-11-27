// Authored by David Thunström
// Date 2025-11-11

#ifndef COMMON
#define COMMON

typedef enum{
    DIR_NONE = -1,
    DIR_UP = 0,
    DIR_DOWN = 1,
    DIR_LEFT = 2,
    DIR_RIGHT = 3
} dir_t;

void dir_to_movement(dir_t dir, int *px, int *py);

#endif