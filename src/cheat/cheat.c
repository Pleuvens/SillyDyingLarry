#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

#include "../structures.h"

int cheated(int w, int h)
{
  int end = 0;

  int zero = 0;
  int one = 0;
  int two = 0;
  int five = 0;
  int six = 0;
  int eight = 0;

  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Window *screen = SDL_CreateWindow("Silly Dying Larry", 0, 0, w, 
                                        h, SDL_WINDOW_OPENGL);


  SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1,
                                              SDL_RENDERER_ACCELERATED
                                              | SDL_RENDERER_PRESENTVSYNC
                                              | SDL_RENDERER_TARGETTEXTURE);

  // music

  Mix_Music *music = NULL;

  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

  music = Mix_LoadMUS("src/music/cheat.mp3");

  if (Mix_PlayingMusic() == 1)
    Mix_HaltMusic();

  Mix_PlayMusic(music, -1);

  // end of music

  SDL_Surface *background = IMG_Load("src/images/menu.png");
  SDL_Surface *cheat = IMG_Load("src/images/Cheat1.png");

  SDL_Texture *backtex = SDL_CreateTextureFromSurface(renderer, background);
  SDL_Texture *cheattex = SDL_CreateTextureFromSurface(renderer, cheat);

  SDL_FreeSurface(background);
  SDL_FreeSurface(cheat);

  SDL_RenderClear(renderer);

  SDL_Rect rect;
  rect.w = w / 2;
  rect.h = h / 4;
  rect.x = (w / 2) - (rect.w / 2);
  rect.y = h / 2 - h / 10;


  SDL_RenderCopy(renderer, backtex, NULL, NULL);

  SDL_RenderCopy(renderer, cheattex, NULL, &rect);

  SDL_RenderPresent(renderer);

  int res = 0;

  while (end == 0)
  {
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
    }

    const Uint8 *keystates = SDL_GetKeyboardState(NULL);

    Uint8 zerod = keystates[SDL_SCANCODE_KP_0];
    Uint8 oned = keystates[SDL_SCANCODE_KP_1];
    Uint8 twod = keystates[SDL_SCANCODE_KP_2];
    Uint8 fived = keystates[SDL_SCANCODE_KP_5];
    Uint8 sixd = keystates[SDL_SCANCODE_KP_6];
    Uint8 eightd = keystates[SDL_SCANCODE_KP_8];

    Uint8 escape = keystates[SDL_SCANCODE_ESCAPE];
    Uint8 enter = keystates[SDL_SCANCODE_KP_ENTER];
    Uint8 enter2 = keystates[SDL_SCANCODE_RETURN];

    if (escape)
      end = 1;

    if (zerod)
      zero = 1;

    if (oned)
      one = 1;

    if (twod)
      two = 1;

    if (fived)
      five = 1;

    if (sixd)
      six = 1;

    if (eightd)
      eight = 1;


    if ((enter || enter2) && zero == 1 && one == 1 && two == 1 && five == 1)
    {
      end = 1;
      res = 1;
    }

    if ((enter || enter2) && zero == 1 && eight == 1 && two == 1 && six == 1)
    {
      end = 1;
      res = 2;
    }
    if (enter || enter2)
    {
      zero = 0;
      one = 0;
      two = 0;
      five = 0;
      six = 0;
      eight = 0;
    }

    SDL_Delay(110);
  }

  SDL_DestroyRenderer(renderer);

  SDL_DestroyWindow(screen);

  return res;
}
