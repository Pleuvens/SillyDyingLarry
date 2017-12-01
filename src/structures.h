#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

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
};

#endif /* !STRUCTURES_H */
