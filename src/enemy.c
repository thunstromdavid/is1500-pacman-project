// Authored by Mathias Jonasson and David Thunström
// Date 2025-11-29

#include "enemy.h"
#include "common.h"
#include "graphics.h"
#include "gamemap.h"


int enemy_configs[NUM_ENEMIES][3] = {
    {24, 18, 0xE0},
    {27, 15, 0x14}, 
    {20, 16, 0xA4}, 
    {23, 19, 0x94}
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
    update_entity_position(&e->base.px, &e->base.py, &e->base.box, &e->base.dir, e->base.req_dir);
    
    int new_dir = get_random(4);
  
    int opposite = (e->base.dir == DIR_NONE) ? -10 : (e->base.dir ^ 1); 

    if (new_dir != opposite) {
        e->base.req_dir = new_dir;
    }
}

static void enemy_render(enemy_t *e) {
    clear_tail(e->base.px, e->base.py, e->base.dir);
    draw_character(e->base.px, e->base.py, e->base.colour);
}

void enemies_update(enemy_t *enemies_array) {
    for (int i = 0; i < NUM_ENEMIES; i++) {
        int old_x = enemies_array[i].base.px;
        int old_y = enemies_array[i].base.py;

        state_mode_enemy(&enemies_array[i]);
        handle_screen_wrap(old_x, old_y, enemies_array[i].base.px, enemies_array[i].base.py);
        enemy_render(&enemies_array[i]);
    }
}

void remove_enemies(enemy_t *enemies_array) {
    for (int i = 0; i < NUM_ENEMIES; i++) {
        remove_character(&enemies_array[i].base);
    }
}

int check_collision_with_enemies(character_t *player, enemy_t *enemies, int num_enemies) {
    for (int i = 0; i < num_enemies; i++) {
        if (check_collision_entity(player, &enemies[i].base.box)) {
            return 1;
        }
    }
    return 0;
}