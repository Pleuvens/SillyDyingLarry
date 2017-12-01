#ifndef VECTOR_H
# define VECTOR_H

struct vector2
{
  float x;
  float y;
};

struct vector2 *vector_create(void);

void vector_destroy(struct vector2 *a);

struct vector2 *add_vect(struct vector2 *a, struct vector2 *b);

struct vector2 *mult_two_vects(struct vector2 *a, struct vector2 *b);

struct vector2 *mult_vect_coef(struct vector2 *a, float coef);

#endif /* !VECTOR_H */
