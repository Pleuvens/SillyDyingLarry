#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "../map/map.h"
#include "../vector/vector.h"
#include "../character/character.h"
#include "../camera/camera.h"
#include "../menu/menu.h"
#include "../level/level.h"

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

void update(struct context *context, char *str, struct current_level *cl)
{
  SDL_RenderClear(context->renderer);

  generate_map(context, str);
  SDL_RenderPresent(context->renderer);

  //SDL_Delay(1000);
  uint64_t time_now = 0;
  uint64_t time_last = 0;

  float frequency = SDL_GetPerformanceFrequency();

  while (1)
  {
    time_last = time_now;
    time_now = SDL_GetPerformanceCounter();

    context->delta_time = (time_now - time_last) * 1000 / frequency;

    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
        return;
    }

    move_character(context, e);

    //Game over
    if (context->player->state == DEAD)
    {
      SDL_RenderClear(context->renderer);
      generate_map(context, str);
      SDL_RenderPresent(context->renderer);
      context->player->state = ALIVE;
      SDL_Delay(1000);
      continue;
    }

    //You won
    if (context->player->state == WON)
    {
      printf("You won!\n");
      SDL_RenderClear(context->renderer);
      generate_map(context, str);
      SDL_RenderPresent(context->renderer);
      context->player->state = ALIVE;
      SDL_Delay(1000);
      cl->win = 1;
      continue;
    }

    move_enemies(context);

    set_camera(context);

    SDL_RenderClear(context->renderer);

    update_map(context);

    SDL_RenderPresent(context->renderer);

    SDL_Delay(60);
  }
}

int main(void)
{
  int screen_width = SCREEN_WIDTH;
  int screen_height = SCREEN_HEIGHT;
  int status = menu(SCREEN_WIDTH, SCREEN_HEIGHT);

  struct current_level *cl = malloc(sizeof (struct current_level));
  cl->lvl1 = 1;
  cl->lvl2 = 1;
  cl->lvl3 = 1;
  cl->lvl4 = 1;
  cl->lvl5 = 0;
  cl->lim = 4;
  cl->win = 0;

  int thislevel = 0;

  while (status != -1)
  {
    if (status == 1)
      status = menu(screen_width, screen_height);
    if (status == 0)
    {
      thislevel = level_selection(screen_width, screen_height, cl);
      if (thislevel != 0)
        status = -1;
      else
        status = 1;
    }
  }

  printf("%d\n", thislevel);

  if (thislevel != 0)
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

    if (thislevel == 1)
      update(context, "maps/level1.map", cl);

    if (thislevel == 2)
      update(context, "maps/level2.map", cl);

    if (thislevel == 3)
      update(context, "maps/level3.map", cl);

    if (thislevel == 4)
      update(context, "maps/level4.map", cl);

    SDL_DestroyWindow(context->window);
    SDL_DestroyRenderer(context->renderer);

    SDL_Quit();
  }

  free(cl);

  return 0;
}
