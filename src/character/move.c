#include <stdio.h>
#include "character.h"
#include "../vector/vector.h"

#define MOVE_SIZE 1
#define GRAVITY 1

void move_character(struct context *c, SDL_Event e)
{
  if (e.type == SDL_KEYDOWN)
  {
    printf("before: x = %f y = %f\n",
          c->player->pos->x, c->player->pos->y);
    float y = c->player->pos->y;
    float x = c->player->pos->x;
    float speed = c->player->speed;
    switch (e.key.keysym.sym)
    {
      case SDLK_UP:
      {
        if (y - MOVE_SIZE >= 0
            && c->map->type[(int)(y-MOVE_SIZE)*c->map->width + (int)x] == NONE)
          c->player->pos->y -= 2*MOVE_SIZE;
        break;
      }
      case SDLK_RIGHT:
      {
        if (x + MOVE_SIZE < c->map->width
            && c->map->type[(int)y*c->map->width + (int)(x+MOVE_SIZE)] == NONE)
          c->player->pos->x += speed;
        break;
      }
      case SDLK_LEFT:
      {
        if (x - MOVE_SIZE >= 0
            && c->map->type[(int)y*c->map->width + (int)(x-MOVE_SIZE)] == NONE)
          c->player->pos->x -= speed;
        break;
      }
      //Down for tests only
      case SDLK_DOWN:
      {
        if (y + MOVE_SIZE < c->map->height
            && c->map->type[(int)(y+MOVE_SIZE)*c->map->width + (int)x] == NONE)
          c->player->pos->y += GRAVITY;
        break;
      }
    }
  }
  float y = c->player->pos->y;
  float x = c->player->pos->x;

  if (y + MOVE_SIZE < c->map->height
    && c->map->type[(int)(y+MOVE_SIZE)*c->map->width + (int)x] == NONE)
    c->player->pos->y += GRAVITY;
  printf("after: x = %f y = %f\n",
          c->player->pos->x, c->player->pos->y);
}
