#ifndef POINTS_H
#define POINTS_H


#define MAX_POINTS 10

typedef struct {
    int tx, ty;     
    int px, py;     
    int active;     
} point_t;

void points_init(point_t *points);


//void point_spawn(void);


void point_render(point_t *points);

#endif