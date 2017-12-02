#include <stdio.h>
#include "character.h"
#include "../vector/vector.h"

#define MOVE_SIZE 1
#define JUMP_FORCE 80
#define GRAVITY 1

static void poor_larry(struct context *context, float d_x, float d_y)
{
  int x = context->player->pos->x + d_x;
  int y = context->player->pos->y + d_y;

  if (!context->enemies)
    return;
  for (int i = 0; i < context->nb_enemies; i++)
  {
    struct character *enemy = context->enemies[i];
    if ((int)enemy->pos->x == x && (int)enemy->pos->y == y)
    {
      context->player->state = DEAD;
      return;
    }
  }
}

static void move_up(struct context *c, float x, float y)
{
  poor_larry(c, 0, -JUMP_FORCE);
  if (y - JUMP_FORCE >= 0
      && c->map->type[(int)(y-JUMP_FORCE)*c->map->width+(int)x] == NONE)
    c->player->pos->y -= JUMP_FORCE / c->delta_time;
}

static void move_right(struct context *c, float x, float y, float speed)
{
  poor_larry(c, speed, 0);
  if (x + speed < c->map->width
      && c->map->type[(int)y*c->map->width+(int)(x+speed)] == NONE)
    c->player->pos->x += speed;
}

static void move_left(struct context *c, float x, float y, float speed)
{
  poor_larry(c, -speed, 0);
  if (x - speed >= 0
      && c->map->type[(int)y*c->map->width+(int)(x-speed)] == NONE)
    c->player->pos->x -= speed;
}

int move_character(struct context *c, SDL_Event e)
{
  (void)e;
  const Uint8 *keystates = SDL_GetKeyboardState(NULL);
  float y = c->player->pos->y;
  float x = c->player->pos->x;
  float speed = c->player->speed * 20 / c->delta_time;

  Uint8 up = keystates[SDL_SCANCODE_UP];
  Uint8 left = keystates[SDL_SCANCODE_LEFT];
  Uint8 right = keystates[SDL_SCANCODE_RIGHT];

  /* Key logic goes here. */

  if (up)
    move_up(c, x, y);
  if (right)
    move_right(c, x, y, speed);
  if (left)
    move_left(c, x, y, speed);

  y = c->player->pos->y;
  x = c->player->pos->x;

  if (y + GRAVITY < c->map->height
      && c->map->type[(int)(y+GRAVITY)*c->map->width + (int)x] == NONE)
    c->player->pos->y += GRAVITY / c->delta_time;

  poor_larry(c, -GRAVITY, 0);
  if (c->map->type[(int)(y+1)*c->map->width+(int)x] == HARMING_GROUND)
    c->player->state = DEAD;

  return 1;
}
