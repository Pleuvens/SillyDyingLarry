#include <stdio.h>
#include "character.h"
#include "../vector/vector.h"

#define MOVE_SIZE 1

void move_character(struct context *c, SDL_Event e)
{
  if (e.type == SDL_KEYDOWN)
  {
    switch (e.key.keysym.sym)
    {
      case SDLK_UP:
      {
        if (c->player->pos->y - MOVE_SIZE >= 0)
          c->player->pos->y -= MOVE_SIZE;
        break;
      }
      case SDLK_RIGHT:
      {
        if (c->player->pos->x + MOVE_SIZE < c->map->width)
          c->player->pos->x += MOVE_SIZE;
        break;
      }
      case SDLK_LEFT:
      {
        if (c->player->pos->x - MOVE_SIZE >= 0)
          c->player->pos->x -= MOVE_SIZE;
        break;
      }
    }
  }
}
