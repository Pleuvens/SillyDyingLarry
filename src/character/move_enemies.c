#include <stdio.h>
#include "character.h"
#include "../vector/vector.h"

#define MOVE_SIZE 0.2
#define GRAVITY 1
#define THRESHOLD 0.8

static int move_enemy(struct context *c, struct character *enemy)
{
  struct character *target = c->player;
  if (target->pos->x < enemy->pos->x)
    enemy->pos->x -= MOVE_SIZE;
  else if (target->pos->x > enemy->pos->x)
    enemy->pos->x += MOVE_SIZE;


  if (enemy->pos->y + MOVE_SIZE  + THRESHOLD < c->map->height
      && c->map->type[(int)(enemy->pos->y + MOVE_SIZE + THRESHOLD) * c->map->width
                      + (int)enemy->pos->x] == NONE)
    enemy->pos->y += GRAVITY;
  return 1;
}

void move_enemies(struct context *c)
{
  for (int i = 0; i < c->nb_enemies; i++)
    move_enemy(c, c->enemies[i]);
}
