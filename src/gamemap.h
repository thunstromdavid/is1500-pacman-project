#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <stdint.h>
#include "graphics.h"
#include "common.h"

#define PATH 0
#define WALL_VERTICAL 1
#define WALL_HORIZONTAL 2
#define WALL_CORNER_TL 3
#define WALL_CORNER_TR 4
#define WALL_CORNER_BL 5
#define WALL_CORNER_BR 6
#define TILE_SIZE 8
#define MAP_WIDTH (SCREEN_WIDTH / TILE_SIZE)
#define MAP_HEIGHT (SCREEN_HEIGHT / TILE_SIZE)

extern int map[MAP_HEIGHT][MAP_WIDTH];

void set_gamemap(void);

#endif
