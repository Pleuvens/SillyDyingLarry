#include "../vector/vector.h"
#include "character.h"

struct character *character_create(void)
{
  struct character *res = calloc(1, sizeof(struct character));
  if (!res)
    return NULL;
  res->pos = create_vect();
  res->speed = 1;
  res->state = ALIVE;
  res->previous_tile = 0;
  return res;
}

void character_destroy(struct character *c)
{
  if (!c)
    return;
  if (c->pos)
    free(c->pos);
  free(c);
}

int character_move(struct character *c, struct vector2 new_pos)
{
  if (new_pos.x < 0 || new_pos.y < 0 || new_pos.x > MAX_POSX
      || new_pos.y > MAX_POSY)
    return -1;
  c->pos->x = new_pos.x;
  c->pos->y = new_pos.y;
  return 0;
}
