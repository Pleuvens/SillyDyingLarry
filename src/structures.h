#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

# define SCREEN_WIDTH 1152 // 1152 - 1280
# define SCREEN_HEIGHT 960 // 960 - 1024

# define SCREEN_BPP 32


enum state
{
  ALIVE = 0,
  DEAD
};

struct character
{
  struct vector2 *pos;
  enum state state;
  float speed;
  int previous_tile;
};

enum type
{
  NONE = 0,
  GROUND = 1,
  HARMING_GROUND = 2
};

struct map
{
  int width;
  int height;
  int *type;
};

struct context {
  SDL_Window *window;
  SDL_Renderer *renderer;
  struct map *map;
  SDL_Texture *backtex;
  SDL_Texture *groundtex;
  SDL_Texture *watertex;
  SDL_Texture *playertex;
  SDL_Texture *enemytex;
  struct character *player;
  SDL_Rect *camera;
  struct character **enemies;
};

struct menu {
  SDL_Surface *background;
  SDL_Surface *button;
};

#endif /* !STRUCTURES_H */
