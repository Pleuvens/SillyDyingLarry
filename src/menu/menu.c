#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "../structures.h"

int main(void)
{
  int end = 0;

  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Window *screen = SDL_CreateWindow("Silly Dying Larry", 0, 0,
                          SCREEN_WIDTH, SCREEN_HEIGHT,
                          SDL_WINDOW_OPENGL);


  SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1,
                                              SDL_RENDERER_ACCELERATED
                                              | SDL_RENDERER_PRESENTVSYNC
                                              | SDL_RENDERER_TARGETTEXTURE);

  SDL_Surface *background = IMG_Load("../../images/menu.png");

  SDL_Surface *button = IMG_Load("../../images/Button.png");

  SDL_Texture *backtex = SDL_CreateTextureFromSurface(renderer, background);
  SDL_Texture *buttex = SDL_CreateTextureFromSurface(renderer, button);

  SDL_RenderClear(renderer);

  SDL_RenderCopy(renderer, backtex, NULL, NULL);
  SDL_RenderCopy(renderer, buttex, NULL, NULL);

  SDL_RenderPresent(renderer);

  while (end == 0)
  {
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
      {
        loop = 0;
        break;
      }
    }

    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, backtex, NULL, NULL);
    SDL_RenderCopy(renderer, buttex, NULL, NULL);

    SDL_RenderPresent(renderer);
  }

  if (background)
    SDL_FreeSurface(background);

  if (button)
    SDL_FreeSurface(button);

  return 0;
}
