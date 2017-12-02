#ifndef VECTOR_H
# define VECTOR_H

#include <stdlib.h>

struct vector2
{
  float x;
  float y;
};

struct vector2 *create_vect(void);

void destroy_vect(struct vector2 *v);

struct vector2 *add_vect(struct vector2 a, struct vector2 b); 

struct vector2 *mult_two_vects(struct vector2 a, struct vector2 b); 

struct vector2 *mult_vect_coef(struct vector2 a, float coef);

double distance_vect(struct vector2 a, struct vector2 b);

#endif /* !VECTOR_H */
