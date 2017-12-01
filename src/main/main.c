#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct context {
  SDL_Window *window;
  SDL_Renderer *renderer;
};

void update(struct context *context)
{
  /*
  while (1)
  {
    SDL_Event e;
    if (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
        break;
    }
  }
  */
  /* Load Background image */
  SDL_Surface *test_surf = IMG_Load("images/background.png");
  SDL_Texture *test_tex = SDL_CreateTextureFromSurface(context->renderer,
                                                       test_surf);
  SDL_FreeSurface(test_surf);
  
  /* ------ */
  
  /* Render Image */

  SDL_RenderClear(context->renderer);
  SDL_RenderCopy(context->renderer, test_tex, NULL, NULL);
  SDL_RenderPresent(context->renderer);

  /* ---- */

  SDL_Delay(10000);

  SDL_DestroyTexture(test_tex);
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
  context->window = SDL_CreateWindow("Rush C", 0, 0, 800, 600,
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
