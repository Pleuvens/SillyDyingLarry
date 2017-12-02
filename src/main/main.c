#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "../map/map.h"

void update(struct context *context)
{
  SDL_RenderClear(context->renderer);

  generate_map(context);

  SDL_RenderPresent(context->renderer);
  
  while (1)
  {
    SDL_Event e;
    if (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
        break;
    }
    SDL_RenderClear(context->renderer);

    update_map(context);

    SDL_RenderPresent(context->renderer);
  }

  SDL_Delay(2000);
}

int main(void)
{
  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO
               | SDL_INIT_EVENTS) != 0)
  {
    SDL_Log("Failed to init SDL: %s\n", SDL_GetError());
    return 1;
  }
  struct context *context = calloc(1, sizeof (struct context));
  context->window = SDL_CreateWindow("Silly Dying Larry", 0, 0, 800, 600,
                                        SDL_WINDOW_OPENGL);
  context->renderer = SDL_CreateRenderer(context->window, -1,
                                              SDL_RENDERER_ACCELERATED
                                              | SDL_RENDERER_PRESENTVSYNC
                                              | SDL_RENDERER_TARGETTEXTURE);

  if (!context->window)
  {
    printf("Failed to create window: %s\n", SDL_GetError());
    return 1;
  }

  update(context);

  SDL_DestroyWindow(context->window);
  SDL_DestroyRenderer(context->renderer);

  SDL_Quit();
  return 0;
}
