#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "../map/map.h"
#include "../vector/vector.h"
#include "../character/character.h"
#include "../camera/camera.h"
#include "../menu/menu.h"

static int init(struct context *context)
{
  context->window = SDL_CreateWindow("Silly Dying Larry", 0, 0, SCREEN_WIDTH,
                                     SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
  context->renderer = SDL_CreateRenderer(context->window, -1,
                                              SDL_RENDERER_ACCELERATED
                                              | SDL_RENDERER_PRESENTVSYNC
                                              | SDL_RENDERER_TARGETTEXTURE);

  if (!context->window)
  {
    printf("Failed to create window: %s\n", SDL_GetError());
    return 1;
  }
  return 0;
}

void update(struct context *context)
{
  SDL_RenderClear(context->renderer);

  generate_map(context);
  SDL_RenderPresent(context->renderer);

  //SDL_Delay(1000);


  while (1)
  {
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
        return;
    }

    move_character(context, e);

    if (context->player->state == DEAD)
    {
      SDL_RenderClear(context->renderer);
      generate_map(context);
      SDL_RenderPresent(context->renderer);
      context->player->state = ALIVE;
      SDL_Delay(1000);
      continue;
    }

    move_enemies(context);

    set_camera(context);

    SDL_RenderClear(context->renderer);

    update_map(context);

    SDL_RenderPresent(context->renderer);

    SDL_Delay(52);
  }
}

int main(void)
{
  int status = menu(SCREEN_WIDTH, SCREEN_HEIGHT);

  printf("salut\n");

  while (status != 0 && status != 1)
  {
    if (status == 1)
      status = menu(1280, 1024);
  }

  if (status == 0)
  {
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO
                 | SDL_INIT_EVENTS) != 0)
    {
      SDL_Log("Failed to init SDL: %s\n", SDL_GetError());
      return 1;
    }

    struct context *context = calloc(1, sizeof (struct context));

    if (init(context) == 1)
      return 1;

    update(context);

    SDL_DestroyWindow(context->window);
    SDL_DestroyRenderer(context->renderer);

    SDL_Quit();
  }

  return 0;
}
