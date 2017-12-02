#ifndef CHARACTER_H
# define CHARACTER_H

#include <SDL2/SDL.h>

#define MAX_POSX 10
#define MAX_POSY 10

enum state
{
  ALIVE = 0,
  DEAD
};

struct character
{
  struct vector2 *pos;
  enum state state;
};

struct character *character_create(void);

void character_destroy(struct character *c);

int character_move(struct character *c, struct vector2 new_pos);

void move_character(struct character *c, SDL_Event e);

#endif /* !CHARACTER_H */
