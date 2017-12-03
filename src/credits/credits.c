#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

#include "../structures.h"

int credits(int w, int h)
{
  int end = 0;

  int cpt = 0;

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

  music = Mix_LoadMUS("src/music/end.mp3");

  if (Mix_PlayingMusic() == 1)
    Mix_HaltMusic();

  Mix_PlayMusic(music, -1);

  // end of music

  SDL_Surface *end1 = IMG_Load("src/images/End1.png");
  SDL_Surface *end2 = IMG_Load("src/images/End2.png");
  SDL_Surface *end3 = IMG_Load("src/images/End3.png");
  SDL_Surface *end4 = IMG_Load("src/images/End4.png");

  SDL_Texture *te1 = SDL_CreateTextureFromSurface(renderer, end1);
  SDL_Texture *te2 = SDL_CreateTextureFromSurface(renderer, end2);
  SDL_Texture *te3 = SDL_CreateTextureFromSurface(renderer, end3);
  SDL_Texture *te4 = SDL_CreateTextureFromSurface(renderer, end4);

  SDL_FreeSurface(end1);
  SDL_FreeSurface(end2);
  SDL_FreeSurface(end3);
  SDL_FreeSurface(end4);

  SDL_RenderClear(renderer);

  SDL_RenderCopy(renderer, te1, NULL, NULL);

  SDL_RenderPresent(renderer);

  SDL_Delay(1000);

  int condition1 = 0;
  int condition2 = 0;
  int condition3 = 0;

  while (end == 0 && cpt != 4)
  {
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
    }

    const Uint8 *keystates = SDL_GetKeyboardState(NULL);

    Uint8 escape = keystates[SDL_SCANCODE_ESCAPE];
    Uint8 enter = keystates[SDL_SCANCODE_KP_ENTER];
    Uint8 enter2 = keystates[SDL_SCANCODE_RETURN];

    if (escape)
      end = 1;

    if (enter || enter2)
      cpt++;

    if (cpt == 1 && condition1 == 0)
    {
      SDL_RenderClear(renderer);

      SDL_RenderCopy(renderer, te2, NULL, NULL);

      SDL_RenderPresent(renderer);

      condition1 = 1;

      SDL_Delay(1000);
    }

    if (cpt == 2 && condition2 == 0)
    {
      SDL_RenderClear(renderer);

      SDL_RenderCopy(renderer, te3, NULL, NULL);

      SDL_RenderPresent(renderer);

      condition2 = 1;

      SDL_Delay(1000);
    }

    if (cpt == 3 && condition3 == 0)
    {
      SDL_RenderClear(renderer);

      SDL_RenderCopy(renderer, te4, NULL, NULL);

      SDL_RenderPresent(renderer);

      condition3 = 1;

      SDL_Delay(1000);
    }


    SDL_Delay(110);
  }

  SDL_DestroyRenderer(renderer);

  SDL_DestroyWindow(screen);

  return 0;
}
