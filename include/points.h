// Authored by David Thunström
// Date 2025-11-10

#ifndef POINTS
#define POINTS

#include "common.h"

#define MAX_POINTS 280 // All avalible path tiles in the map for points to spawn
#define POINT_VALUE 10

typedef struct {
    int active;     

    Rect box;
} point_t;

void points_init(point_t *points);
void point_render(point_t *points);
int check_point_collision(Rect *box, point_t *points);

#endif