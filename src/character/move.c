#include <stdio.h>
#include "character.h"
#include "../vector/vector.h"

#define MOVE_SIZE 1
#define GRAVITY 1

static void move_up(struct context *c, float x, float y)
{
  if (y - MOVE_SIZE >= 0
      && c->map->type[(int)(y-MOVE_SIZE)*c->map->width+(int)x] == NONE)
    c->player->pos->y -= 2*MOVE_SIZE;
}

static void move_right(struct context *c, float x, float y, float speed)
{
  if (x + MOVE_SIZE < c->map->width
      && c->map->type[(int)y*c->map->width+(int)(x+MOVE_SIZE)] == NONE)
    c->player->pos->x += speed;
}

static void move_left(struct context *c, float x, float y, float speed)
{
  if (x - MOVE_SIZE >= 0
      && c->map->type[(int)y*c->map->width+(int)(x-MOVE_SIZE)] == NONE)
    c->player->pos->x -= speed;
}
/*
static void move_down(struct context *c, float x, float y)
{
  if ((y + (2*MOVE_SIZE)) >= 0 && x - MOVE_SIZE >= 0
      && c->map->type[(int)(y-MOVE_SIZE)*c->map->width+(int)x] == NONE)
  {
    c->player->pos->y += 2*MOVE_SIZE;
    if (c->map->type[(int)(y+1)*c->map->width+(int)x] == HARMING_GROUND)
      c->player->state = DEAD;
  } 
}*/


int move_character(struct context *c, SDL_Event e)
{
  (void)e;
  const Uint8 *keystates = SDL_GetKeyboardState(NULL);
  float y = c->player->pos->y;
  float x = c->player->pos->x;
  float speed = c->player->speed;

  Uint8 up = keystates[SDL_SCANCODE_UP];
  //Uint8 down = keystates[SDL_SCANCODE_DOWN];
  Uint8 left = keystates[SDL_SCANCODE_LEFT];
  Uint8 right = keystates[SDL_SCANCODE_RIGHT];

  /* Key logic goes here. */
  //printf("before: x = %f y = %f\n", c->player->pos->x, c->player->pos->y);

  if (up)
    move_up(c, x, y);
  if (right)
    move_right(c, x, y, speed);
  if (left)
    move_left(c, x, y, speed);
  //Down for tests only
  //if (down)
    //move_down(c, x, y);

  y = c->player->pos->y;
  x = c->player->pos->x;

  if (y + MOVE_SIZE < c->map->height
      && c->map->type[(int)(y+MOVE_SIZE)*c->map->width + (int)x] == NONE)
    c->player->pos->y += GRAVITY;

  if (c->map->type[(int)(y+1)*c->map->width+(int)x] == HARMING_GROUND)
    c->player->state = DEAD;
  //printf("after: x = %f y = %f\n", c->player->pos->x, c->player->pos->y);

  return 1;
}
