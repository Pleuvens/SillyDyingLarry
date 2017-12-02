#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

# define SCREEN_WIDTH 800 // 800 - 1152 - 1280 - 1792 - 1920
# define SCREEN_HEIGHT 608 // 608 - 960 - 1024 - 1136 - 1200
# define MAX_JUMP 4

# define SCREEN_BPP 32


enum state
{
  ALIVE = 0,
  DEAD,
  WON
};

enum move
{
  LEFT = 0,
  RIGHT
};

struct rect {
  float x;
  float y;
  int w;
  int h;
};

struct character
{
  struct vector2 *pos;
  enum state state;
  float speed;
  int previous_tile;
  enum move move;
  SDL_Rect rect;
  float jumpf;
};

enum type
{
  NONE = 0,
  GROUND = 1,
  HARMING_GROUND = 2,
  END = 5
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
  SDL_Texture *endtex;
  struct character *player;
  struct rect *camera;
  int nb_enemies;
  struct character **enemies;
  float delta_time;
};

struct button {
  SDL_Texture *backtex;
  SDL_Texture *btexpo; 
  SDL_Texture *btexpf;
  SDL_Texture *btexoo;
  SDL_Texture *btexof;
  SDL_Texture *btexqo;
  SDL_Texture *btexqf;
};

#endif /* !STRUCTURES_H */
