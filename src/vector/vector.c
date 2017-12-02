#include <math.h>
#include "vector.h"

struct vector2 *create_vect(void)
{
  struct vector2 *new = calloc(1, sizeof(struct vector2));
  if (!new)
    return NULL;
  return new;
}

void destroy_vect(struct vector2 *v)
{
  if (!v)
    return;
  free(v);
}

struct vector2 *add_vect(struct vector2 a, struct vector2 b)
{
  struct vector2 *res = create_vect();

  if (!res)
    return NULL;
  res->x = a.x + b.x;
  res->y = a.y + b.y;
  return res;
}
struct vector2 *mult_two_vects(struct vector2 a, struct vector2 b)
{
  struct vector2 *res = create_vect();

  if (!res)
    return NULL;
  res->x = a.x * b.x;
  res->y = a.y * b.y;
  return res;
}

struct vector2 *mult_vect_coef(struct vector2 a, float coef)
{
  struct vector2 *res = create_vect();

  if (!res)
    return NULL;
  res->x = a.x * coef;
  res->y = a.y * coef;
  return res;
}

double distance_vect(struct vector2 a, struct vector2 b)
{
  return sqrt(pow(a.x - b.x, 1) + pow(a.y - b.y, 2));
}
