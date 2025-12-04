// Authored by David Thunström
// Date 2025-11-11

#ifndef COMMON
#define COMMON

typedef struct {
    int x, y;
    int w, h;
} Rect;

typedef enum{
    DIR_NONE = -1,
    DIR_UP = 0,
    DIR_DOWN = 1,
    DIR_LEFT = 2,
    DIR_RIGHT = 3
} dir_t;

typedef struct {
    int tx, ty;          // Tile Position
    int px, py;          // Pixel Position
    dir_t dir, req_dir;  // Directions
    int colour;
    Rect box;
} character_t;

void character_init(character_t *c, int tx, int ty, int colour);

int get_random(int range);

void dir_to_movement(dir_t dir, int *px, int *py);

int check_rect_collision(Rect *r1, Rect *r2);

int check_collision_entity(character_t *p, Rect *r);

int check_collision_entities(character_t *p, character_t *e, int num_enemies);

int can_move_to(int tx, int ty);

int is_centered(int val);

void update_entity_position(int *px, int *py, Rect *box, dir_t *current_dir, dir_t req_dir, int speed);

void remove_character(character_t *c);

#endif