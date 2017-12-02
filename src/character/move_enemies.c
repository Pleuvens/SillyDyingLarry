#include <stdio.h>
#include "character.h"
#include "../vector/vector.h"

#define MOVE_SIZE 0.15
#define GRAVITY 1
#define THRESHOLD 0.85
#define MIN_DISTANCE 7

int floor_is_valid(struct context *c, float x, float y)
{
  return c->map->type[(int)(y+1)*c->map->width+(int)x] != HARMING_GROUND;
}

static int move_enemy(struct context *c, struct character *enemy)
{
  struct character *target = c->player;

  if (abs(distance_vect(*(target->pos), *(enemy->pos))) < MIN_DISTANCE)
  {
    if (target->pos->x < enemy->pos->x
      && floor_is_valid(c, enemy->pos->x-(MOVE_SIZE+THRESHOLD), enemy->pos->y))
      enemy->pos->x -= MOVE_SIZE;
    else if (target->pos->x > enemy->pos->x
      && floor_is_valid(c, enemy->pos->x+(MOVE_SIZE+THRESHOLD), enemy->pos->y))
      enemy->pos->x += MOVE_SIZE;


    if (enemy->pos->y + MOVE_SIZE  + THRESHOLD < c->map->height
        && c->map->type[(int)(enemy->pos->y + MOVE_SIZE + THRESHOLD)
           * c->map->width + (int)enemy->pos->x] == NONE)
      enemy->pos->y += GRAVITY;
  }
  else
  {
    if (enemy->move == LEFT)
    {
      if (floor_is_valid(c, enemy->pos->x-(MOVE_SIZE+THRESHOLD), enemy->pos->y))
        enemy->pos->x -= MOVE_SIZE;
      else
        enemy->move = RIGHT;
    }
    else if (enemy->move == RIGHT)
    {
      if (floor_is_valid(c, enemy->pos->x+(MOVE_SIZE+THRESHOLD), enemy->pos->y))
        enemy->pos->x += MOVE_SIZE;
      else
        enemy->move = LEFT;
    }
  }
  return 1;
}

void move_enemies(struct context *c)
{
  for (int i = 0; i < c->nb_enemies; i++)
    move_enemy(c, c->enemies[i]);
}
