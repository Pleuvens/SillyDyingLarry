#include <stdio.h>
#include "character.h"
#include "../vector/vector.h"

#define MOVE_SIZE 0.15
#define GRAVITY 1
#define THRESHOLD 0.85
#define MIN_DISTANCE 5

static int is_over_ground(struct context *c, float x, float y)
{
  for (int i = 0; (y + i) < c->map->height; i++)
  {
    if (c->map->type[(int)(y+i)*c->map->width+(int)x] == GROUND)
      return 0;
  }
  return 1;
}

static int floor_is_valid(struct context *c, float x, float y)
{
  return c->map->type[(int)(y+1)*c->map->width+(int)x] != HARMING_GROUND;
}

static int move_enemy(struct context *c, struct character *enemy)
{
  struct character *target = c->player;
  float y = enemy->pos->y;
  float x = enemy->pos->x;

  if (c->map->type[(int)(y+1)*c->map->width+(int)x] != GROUND)
  {
    if (abs(distance_vect(*(target->pos), *(enemy->pos))) < MIN_DISTANCE)
    {
      if (target->pos->x < x)
        enemy->pos->x -= MOVE_SIZE;
      else if (target->pos->x > x)
        enemy->pos->x += MOVE_SIZE;
      if (target->pos->y < y)
        enemy->pos->y -= MOVE_SIZE;
      else if (target->pos->y > y)
        enemy->pos->y += MOVE_SIZE;
    }
    else
    {
      if (enemy->move == LEFT)
      {
        if (is_over_ground(c, x-(MOVE_SIZE+THRESHOLD), y) == 0)
          enemy->pos->x -= MOVE_SIZE;
        else
          enemy->move = RIGHT;
      }
      else if (enemy->move == RIGHT)
      {
        if (is_over_ground(c, x+(MOVE_SIZE+THRESHOLD), y) == 0)
          enemy->pos->x += MOVE_SIZE;
        else
          enemy->move = LEFT;
      }
    }
  }
  else
  {
    if (abs(distance_vect(*(target->pos), *(enemy->pos))) < MIN_DISTANCE)
    {
      if (target->pos->x < x && floor_is_valid(c, x-(MOVE_SIZE+THRESHOLD), y))
        enemy->pos->x -= MOVE_SIZE;
      else if (target->pos->x > x &&floor_is_valid(c,x+(MOVE_SIZE+THRESHOLD),y))
        enemy->pos->x += MOVE_SIZE;
    }
    else
    {
      if (enemy->move == LEFT)
      {
        if (floor_is_valid(c, x-(MOVE_SIZE+THRESHOLD), y))
          enemy->pos->x -= MOVE_SIZE;
        else
          enemy->move = RIGHT;
      }
      else if (enemy->move == RIGHT)
      {
        if (floor_is_valid(c, x+(MOVE_SIZE+THRESHOLD), y))
          enemy->pos->x += MOVE_SIZE;
        else
          enemy->move = LEFT;
      }
    }
  }
  poor_larry(c, 0,0);
  return 1;
}

void move_enemies(struct context *c)
{
  for (int i = 0; i < c->nb_enemies; i++)
    move_enemy(c, c->enemies[i]);
}
