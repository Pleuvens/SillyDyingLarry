#include "../main/main.h"
#include "map.h"

int *parse_file(char *path)
{
  int width = 0;
  int height = 0;
  
  int *map = calloc(width * height, sizeof (int));

  for (int i = 0; i < width; ++i)
  {
    for (int j = 0; j < height; ++j)
    {

    }
  }
}

void generate_map(struct context *context)
{
  SDL_Surface *test_surf = IMG_Load("images/background_tile.png");
  SDL_Texture *test_tex = SDL_CreateTextureFromSurface(context->renderer,
                                                       test_surf);
  SDL_FreeSurface(test_surf);

  int width = 800 / TILE_WIDTH;
  int height = 600 / TILE_HEIGHT;

  for (int i = 0; i <= width; i++)
  {
    for (int j = 0; j <= height; ++j)
    {
      SDL_Rect dst = { i * 32, j * 32, 32, 32};
      SDL_RenderCopy(context->renderer, test_tex, NULL, &dst);
    }
  }
}

/*
  SDL_Surface *test_surf = IMG_Load("images/background.png");
  SDL_Texture *test_tex = SDL_CreateTextureFromSurface(context->renderer,
                                                       test_surf);
  SDL_FreeSurface(test_surf);


  SDL_RenderClear(context->renderer);
  SDL_RenderCopy(context->renderer, test_tex, NULL, NULL);
  SDL_RenderPresent(context->renderer);

*/
