#include <SDL2/SDL.h>
#include <stdio.h>
#include "character.h"

#define MOVE_SIZE 10

void move_character(struct character *c, SDL_Event e)
{
  else if(e.type == SDL_KEYDOWN)
  {
    switch(e.key.keysym.sym)
    {
      case SDLK_UP:
      {
        c->pos->y += MOVE_SIZE;
        break;
      }
      case SDLK_RIGHT:
      {
        c->pos->x += MOVE_SIZE;
        break;
      }
      case SDLK_LEFT:
      {
        c->pos->x -= MOVE_SIZE;
        break;
      }
    }
  }
}
