#include <stdio.h>
#include "character.h"
#include "../vector/vector.h"

#define MOVE_SIZE 1
#define JUMP_FORCE 5
#define GRAVITY 14
#define MAX_FALL_SPEED 3

void poor_larry(struct context *context, float d_x, float d_y)
{
  int x = context->player->pos->x + d_x;
  int y = context->player->pos->y + d_y;

  if (!context->enemies)
    return;
  for (int i = 0; i < context->nb_enemies; i++)
  {
    struct character *enemy = context->enemies[i];
    if (enemy->pos->x <= x + 0.5 && enemy->pos->x >= x - 0.5
        && enemy->pos->y<= y + 0.5 && enemy->pos->y>= y - 0.5)
    {
      context->player->state = DEAD;
      return;
    }
  }
}

static void cool_larry(struct context *context, float d_x, float d_y)
{
  int x = context->player->pos->x + d_x;
  int y = context->player->pos->y + d_y;

  if (context->map->type[(int)roundf(y+1)*context->map->width+(int)roundf(x)] == END)
    context->player->state = WON;
}

static void move_up(struct context *c, float x, float y)
{
  poor_larry(c, 0, -MOVE_SIZE);
  if (c->player->state != ALIVE)
    return;
  if (c->player->jumpf
      || c->map->type[(int)roundf(y+MOVE_SIZE)*c->map->width + (int)roundf(x)] == NONE
      || c->map->type[(int)roundf(y+MOVE_SIZE)*c->map->width + (int)roundf(x)] == HARMING_GROUND)
    return;
  if (y - JUMP_FORCE / c->delta_time >= 0
      && c->map->type[(int)roundf(y-JUMP_FORCE)*c->map->width+(int)roundf(x)] == NONE)
    c->player->jumpf = JUMP_FORCE;
}

static void move_right(struct context *c, float x, float y, float speed)
{
  poor_larry(c, MOVE_SIZE, 0);
  if (c->player->state != ALIVE)
    return;
 
  if (x + speed < c->map->width
      && c->map->type[(int)roundf(y)*c->map->width+(int)roundf(x+speed)] == NONE)
    c->player->pos->x += speed;
}

static void move_left(struct context *c, float x, float y, float speed)
{
  poor_larry(c, -MOVE_SIZE, 0);
  if (c->player->state != ALIVE)
    return;
 
  if (x - speed >= 0
      && c->map->type[(int)roundf(y)*c->map->width+(int)roundf(x-speed)] == NONE)
    c->player->pos->x -= speed;
}

int move_character(struct context *c, SDL_Event e)
{

  (void)e;
  const Uint8 *keystates = SDL_GetKeyboardState(NULL);
  float y = c->player->pos->y;
  float x = c->player->pos->x;
  float speed = c->player->speed * 20 / c->delta_time;
  
  cool_larry(c, 0, 0);
  cool_larry(c, 0, 1);
  cool_larry(c, 0, -1);
  cool_larry(c, 1, 0);
  cool_larry(c, -1, 0);
  if (c->map->type[(int)roundf(y)*c->map->width+(int)roundf(x)] == HARMING_GROUND)
    c->player->state = DEAD;

  Uint8 up = keystates[SDL_SCANCODE_UP];
  Uint8 left = keystates[SDL_SCANCODE_LEFT];
  Uint8 quit = keystates[SDL_SCANCODE_ESCAPE];
  Uint8 right = keystates[SDL_SCANCODE_RIGHT];

  /* Key logic goes here. */
  if (up)
    move_up(c, x, y);
  if (right)
    move_right(c, x, y, speed);
  if (left)
    move_left(c, x, y, speed);
  if (quit)
    return -1;

  y = c->player->pos->y;
  x = c->player->pos->x;
  

  if (c->player->jumpf)
  {
    c->player->pos->y += -speed*c->player->jumpf + GRAVITY /(c->player->jumpf * c->delta_time);
    c->player->jumpf -= MOVE_SIZE;
    if (c->player->jumpf < 0)
      c->player->jumpf = 0;
  }
  else if (y + GRAVITY * c->fall_speed / c->delta_time < c->map->height
      && (c->map->type[(int)roundf(y+GRAVITY * c->fall_speed / c->delta_time)*c->map->width + (int)roundf(x)] == NONE
        || c->map->type[(int)roundf(y+GRAVITY * c->fall_speed / c->delta_time)*c->map->width + (int)roundf(x)] == HARMING_GROUND))
  {
    if (c->map->type[(int)roundf(y+GRAVITY * c->fall_speed / c->delta_time)*c->map->width + (int)roundf(x)] == GROUND)
      c->fall_speed = 0;
    else
    {
      c->player->pos->y += GRAVITY * c->fall_speed / c->delta_time;
      if (c->fall_speed < MAX_FALL_SPEED)
        c->fall_speed += MOVE_SIZE;
    }
  }
  else
    c->fall_speed = 1;

  cool_larry(c, 0, 0);
  cool_larry(c, 0, 1);
  cool_larry(c, 0, -1);
  cool_larry(c, 1, 0);
  cool_larry(c, -1, 0);
  poor_larry(c, -MOVE_SIZE, 0);
  return 1;
}
