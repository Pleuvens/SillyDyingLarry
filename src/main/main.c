#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "../map/map.h"
#include "../vector/vector.h"
#include "../character/character.h"
#include "../camera/camera.h"
#include "../menu/menu.h"
#include "../level/level.h"
#include "../cheat/cheat.h"
#include "../credits/credits.h"

SDL_Surface *deathd(int cpt)
{
  SDL_Surface *death = IMG_Load("src/images/gameover1.png");

  if (cpt == 2)
    death = IMG_Load("src/images/gameover2.png");

  if (cpt == 3)
    death = IMG_Load("src/images/gameover3.png");

  if (cpt == 4)
    death = IMG_Load("src/images/gameover4.png");

  if (cpt == 5)
    death = IMG_Load("src/images/gameover5.png");

  if (cpt == 6)
    death = IMG_Load("src/images/gameover6.png");

  return death;
}


static int init(struct context *context, int w, int h)
{
  context->window = SDL_CreateWindow("Silly Dying Larry", 0, 0, w,
                                     h, SDL_WINDOW_OPENGL);
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

  uint64_t time_now = 0;
  uint64_t time_last = 0;

  float frequency = SDL_GetPerformanceFrequency();

  int cpt_death = 0;
  int error = 0;

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

    error = move_character(context, e);

    if (error == -1)
      break;

    if (error == -2)
    {
      SDL_RenderClear(context->renderer);

      generate_map(context, str);
      SDL_RenderPresent(context->renderer);
      continue;
    }

    //Game over
    if (context->player->state == DEAD)
    {
      cpt_death++;

      SDL_RenderClear(context->renderer);

      SDL_Surface *death = deathd(cpt_death);
      SDL_Texture *dt = SDL_CreateTextureFromSurface(context->renderer, death);
      SDL_FreeSurface(death);
      SDL_RenderCopy(context->renderer, dt, NULL, NULL);
      SDL_RenderPresent(context->renderer);
      SDL_DestroyTexture(dt);

      SDL_Delay(2500);

      if (cpt_death == 6)
        break;
      
      SDL_RenderClear(context->renderer);
      generate_map(context, str);
      SDL_RenderPresent(context->renderer);
      context->player->state = ALIVE;
      SDL_Delay(250);
      continue;
    }

    //You won
    if (context->player->state == WON)
    {
      context->player->state = ALIVE;

      SDL_RenderClear(context->renderer);

      SDL_Surface *lp = IMG_Load("src/images/lvlpassed2.png");
      SDL_Texture *texp = SDL_CreateTextureFromSurface(context->renderer, lp);
      SDL_RenderCopy(context->renderer, texp, NULL, NULL);

      SDL_RenderPresent(context->renderer);
      SDL_Delay(5000);

      cl->win = 1;
      break;
    }

    move_enemies(context);

    set_camera(context);

    SDL_RenderClear(context->renderer);

    update_map(context);

    SDL_RenderPresent(context->renderer);

    SDL_Delay(60);
  }


  cl->curr = cpt_death;

  if (cpt_death == 6)
  {
    cl->lvl2 = 0;
    cl->lvl3 = 0;
    cl->lvl4 = 0;
    cl->lvl5 = 0;
    cl->win = 0;
    cl->lim = 1;
    cl->curr = 0;
  }
}

int main(int argc, char *argv[])
{
  int conditionwin = 0;

  int screen_width = SCREEN_WIDTH;
  int screen_height = SCREEN_HEIGHT;

  if (argc == 3)
  {
    screen_width = atoi(argv[1]);
    screen_height = atoi(argv[2]);
  }
  
  int status = menu(screen_width, screen_height);

  struct current_level *cl = malloc(sizeof (struct current_level));
  cl->lvl1 = 1;
  cl->lvl2 = 0;
  cl->lvl3 = 0;
  cl->lvl4 = 0;
  cl->lvl5 = 0;
  cl->lim = 1;
  cl->win = 0;

  Mix_Music *music = NULL;
  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

  int thislevel = 0;
  int cheat = 0;

  while (status != -1)
  {
    if (conditionwin == 1)
    {
      credits(screen_width, screen_height);
      status = 1;
      conditionwin = 0;
    }

    if (status == 1)
    {
      thislevel = 0;
      status = menu(screen_width, screen_height);
    }

    if (status == 2)
    {
      thislevel = 0;
      cheat = cheated(screen_width, screen_height);
      if (cheat == 1)
      {
        cl->lvl1 = 1;
        cl->lvl2 = 1;
        cl->lvl3 = 1;
        cl->lvl4 = 1;
        cl->lvl5 = 1;
        cl->lim = 5;
      }
      else if (cheat == 2)
        conditionwin = 1;

      cheat = 0;
      status = 1;
    }

    if (status == 0)
    {
      thislevel = level_selection(screen_width, screen_height, cl);
      status = 1;
    }

    if (status == -1)
      break;

    if (thislevel != 0)
    {
      if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO
                 | SDL_INIT_EVENTS) != 0)
      {
        SDL_Log("Failed to init SDL: %s\n", SDL_GetError());
        return 1;
      }

      struct context *context = calloc(1, sizeof (struct context));

      if (init(context, screen_width, screen_height) == 1)
        return 1;

      if (thislevel == 1)
      {
        music = Mix_LoadMUS("src/music/lvl1.mp3");
        if (Mix_PlayingMusic() == 1)
          Mix_HaltMusic();
        Mix_PlayMusic(music, -1);
        
        update(context, "src/maps/level1.map", cl);
        if (cl->win == 1)
        {
          cl->win = 0;
          cl->lvl2 = 1;
          if (cl->lim < 2)
            cl->lim = 2;
          cl->curr = 0;
        }
      }

      if (thislevel == 2)
      {
        music = Mix_LoadMUS("src/music/lvl2.mp3");
        if (Mix_PlayingMusic() == 1)
          Mix_HaltMusic();
        Mix_PlayMusic(music, -1);

        update(context, "src/maps/level2.map", cl);
        if (cl->win == 1)
        {
          cl->win = 0;
          cl->lvl3 = 1;
          if (cl->lim < 3)
            cl->lim = 3;
          cl->curr = 0;
        }
      }

      if (thislevel == 3)
      {
        music = Mix_LoadMUS("src/music/lvl3.mp3");
        if (Mix_PlayingMusic() == 1)
          Mix_HaltMusic();
        Mix_PlayMusic(music, -1);

        update(context, "src/maps/level3.map", cl);
        if (cl->win == 1)
        {
          cl->win = 0;
          cl->lvl4 = 1;
          if (cl->lim < 4)
            cl->lim = 4;
          cl->curr = 0;
        }
      }

      if (thislevel == 4)
      {  
        music = Mix_LoadMUS("src/music/lvl4.mp3");
        if (Mix_PlayingMusic() == 1)
          Mix_HaltMusic();
        Mix_PlayMusic(music, -1);

        update(context, "src/maps/level4.map", cl);
        if (cl->win == 1)
        {
          cl->win = 0;
          cl->lvl5 = 1;
          cl->lim = 5;
          cl->curr = 0;
        }
      }

      if (thislevel == 5)
      {
        music = Mix_LoadMUS("src/music/lvl5.mp3");
        if (Mix_PlayingMusic() == 1)
          Mix_HaltMusic();
        Mix_PlayMusic(music, -1);

        update(context, "src/maps/level5.map", cl);
        if (cl->win == 1)
        {
          cl->curr = 0;
          cl->win = 0;
          conditionwin = 1;
        }
      }

      SDL_DestroyWindow(context->window);
      SDL_DestroyRenderer(context->renderer);
    }
    status = 1;
  }

  free(cl);

  SDL_Quit();

  return 0;
}
