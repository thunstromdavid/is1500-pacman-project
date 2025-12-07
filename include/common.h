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
    DIR_DOWN = 0,
    DIR_UP = 1,
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
int get_diff(int a, int b);
int check_rect_collision(Rect *r1, Rect *r2);
int check_collision_entity(character_t *p, Rect *r);
void update_entity_position(int *px, int *py, Rect *box, dir_t *current_dir, dir_t req_dir);
void remove_character(character_t *c);
#endif