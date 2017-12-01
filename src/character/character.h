#ifndef CHARACTER_H
# define CHARACTER_H

enum state
{
  ALIVE = 0,
  DEAD
};

struct character
{
  struct vector2 *pos;
  enum state state;
};

#endif /* !CHARACTER_H */
