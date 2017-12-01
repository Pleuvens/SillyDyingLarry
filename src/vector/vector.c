#include <stdlib.h>
#include "vector.h"

struct vector2 *vector_create(void)
{
  struct vector2 *new = calloc(1, sizeof(struct vector2));
  if (!new)
    return NULL;
  return new;
}

void vector_destroy(struct vector2 *a)
{
  free(a);
}

struct vector2 *add_vect(struct vector2 *a, struct vector2 *b)
{
  struct vector2 *res = vector_create();
  res->x = a->x + b->x;
  res->y = a->y + b->y;
  return res;
}

struct vector2 *mult_two_vects(struct vector2 *a, struct vector2 *b)
{
  struct vector2 *res = vector_create();
  res->x = a->x * b->x;
  res->y = a->y * b->y;
  return res;
}

struct vector2 *mult_vect_coef(struct vector2 *a, float coef)
{
  struct vector2 *res = vector_create();
  res->x = a->x * coef;
  res->y = a->y * coef;
  return res;
}
