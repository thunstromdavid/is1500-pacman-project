#ifndef ENEMY
#define ENEMY
#include "game.h"
#include "common.h"

typedef struct {
    
    int px;
    int py;
    
    int tx;
    int ty;

    dir_t dir;
    dir_t req_dir; 
} enemy_t;

void m