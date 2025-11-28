#ifndef POINTS
#define POINTS

#include "common.h"

#define MAX_POINTS 300
#define POINT_VALUE 10

typedef struct {
    int tx, ty;     
    int px, py;     
    int active;     

    Rect box;
} point_t;

void points_init(point_t *points);


//void point_spawn(void);


void point_render(point_t *points);

int check_point_collision(Rect *box, point_t *points);

#endif