#ifndef CHARACTER_H
# define CHARACTER_H

#include <SDL2/SDL.h>
#include "../structures.h"

#define MAX_POSX 10
#define MAX_POSY 10

struct character *character_create(void);

void character_destroy(struct character *c);

int character_move(struct character *c, struct vector2 new_pos);

int move_character(struct context *c, SDL_Event e);

void move_enemies(struct context *c);

#endif /* !CHARACTER_H */
