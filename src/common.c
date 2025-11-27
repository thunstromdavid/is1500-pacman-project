#include "common.h"
#include "gamemap.h"

static unsigned int next_random = 1; 

// "Fake" Random function 
int get_random(int range) {
    next_random = next_random * 1103515245 + 12345;
    return ((unsigned int)(next_random / 65536) % 32768) % range;
}

void dir_to_movement(dir_t dir, int *px, int *py) {
    switch (dir) {
        case DIR_UP:    
            *px = 0;  
            *py = -1; 
            break;
        case DIR_DOWN:  
            *px = 0;  
            *py = 1; 
            break;
        case DIR_LEFT:  
            *px = -1; 
            *py = 0;  
            break;
        case DIR_RIGHT: 
            *px = 1;  
            *py = 0;  
            break;
        default:          
            *px = 0;  
            *py = 0; 
            break;
    }
}    

    int can_move_to(int tx, int ty){
    if (ty < 0 || ty >= MAP_HEIGHT){
        return 0;
    }

    if ((tx < 0 || tx >= MAP_WIDTH) && ty == 14){
        return 1; 
    }
    return map[ty][tx] == PATH;
}
