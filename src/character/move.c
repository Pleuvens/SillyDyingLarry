#include <stdio.h>
#include "character.h"
#include "../vector/vector.h"

#define MOVE_SIZE 1
#define GRAVITY 1

int move_character(struct context *c, SDL_Event e)
{
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      return 0;
    }
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    Uint8 up = keystates[SDL_SCANCODE_UP];
    Uint8 down = keystates[SDL_SCANCODE_DOWN];
    Uint8 left = keystates[SDL_SCANCODE_LEFT];
    Uint8 right = keystates[SDL_SCANCODE_RIGHT];
    /* Key logic goes here. */
    //if (e.type == SDL_KEYDOWN)
    //{
      printf("before: x = %f y = %f\n",
            c->player->pos->x, c->player->pos->y);
      float y = c->player->pos->y;
      float x = c->player->pos->x;
      float speed = c->player->speed;
      //switch (e.key.keysym.sym)
      //{
        //case SDLK_UP:
        if (up)
        {
          if (y - MOVE_SIZE >= 0
              && c->map->type[(int)(y-MOVE_SIZE)*c->map->width+(int)x] == NONE)
            c->player->pos->y -= 2*MOVE_SIZE;
          break;
        }
        if (right)
        //case SDLK_RIGHT:
        {
          if (x + MOVE_SIZE < c->map->width
              && c->map->type[(int)y*c->map->width+(int)(x+MOVE_SIZE)] == NONE)
            c->player->pos->x += speed;
          break;
        }
        //case SDLK_LEFT:
        if (left)
        {
          if (x - MOVE_SIZE >= 0
              && c->map->type[(int)y*c->map->width+(int)(x-MOVE_SIZE)] == NONE)
            c->player->pos->x -= speed;
          break;
        }
        if (down)
        //Down for tests only
        //case SDLK_DOWN:
        if (up && left)
        {
          if (x - MOVE_SIZE >= 0
              && c->map->type[(int)y*c->map->width+(int)(x-MOVE_SIZE)] == NONE
              && c->map->type[(int)(y+MOVE_SIZE)*c->map->width+(int)x] == NONE)
          {
            c->player->pos->x -= speed;
            c->player->pos->y += GRAVITY;
            break;
          }
          if (y - MOVE_SIZE >= 0 && x - MOVE_SIZE >= 0
              && c->map->type[(int)(y-MOVE_SIZE)*c->map->width+(int)x] == NONE)
            c->player->pos->y -= 2*MOVE_SIZE;
          break;
 
        }
      //}
    //}
  }
  float y = c->player->pos->y;
  float x = c->player->pos->x;
  if (y + MOVE_SIZE < c->map->height
    && c->map->type[(int)(y+MOVE_SIZE)*c->map->width + (int)x] == NONE)
    c->player->pos->y += GRAVITY;
  printf("after: x = %f y = %f\n",
          c->player->pos->x, c->player->pos->y);
  return 1;
}
