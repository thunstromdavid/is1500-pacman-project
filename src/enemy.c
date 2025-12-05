#include "enemy.h"
#include "common.h"
#include "graphics.h"


int enemy_configs[NUM_ENEMIES][3] = {
    {24, 18, 0xE0},
    {27, 15, 0x14}, 
    {20, 16, 0xA4}, 
    {23, 18, 0x94}
};

void enemy_init(enemy_t *e, int posx, int posy, int colour) {
    character_init(&e->base, posx, posy, colour);
}

void enemies_init(enemy_t *enemies_array) {
    for (int i = 0; i < NUM_ENEMIES; i++) {
        enemy_init(&enemies_array[i], 
                   enemy_configs[i][0], 
                   enemy_configs[i][1], 
                   enemy_configs[i][2]);
    }
}

void state_mode_enemy(enemy_t *e) {
    update_entity_position(&e->base.px, &e->base.py, &e->base.box, &e->base.dir, e->base.req_dir, 1);
    
    int new_dir = get_random(4);
  
    int opposite = (e->base.dir == DIR_NONE) ? -10 : (e->base.dir ^ 1); 

    if (new_dir != opposite) {
        e->base.req_dir = new_dir;
    }
}

void enemy_render(enemy_t *e) {
    draw_character(e->base.px, e->base.py, e->base.colour);
    redraw_tile(e->base.px, e->base.py, e->base.dir);
}

void enemies_update(enemy_t *enemies_array) {
    for (int i = 0; i < NUM_ENEMIES; i++) {
        state_mode_enemy(&enemies_array[i]);
        enemy_render(&enemies_array[i]);
    }
}

void remove_enemies(enemy_t *enemies_array) {
    for (int i = 0; i < NUM_ENEMIES; i++) {
        remove_character(&enemies_array[i].base);
    }
}