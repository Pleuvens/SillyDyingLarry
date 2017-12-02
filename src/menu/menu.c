#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

#include "../structures.h"

int menu(int screen_w, int screen_h)
{
  int end = 0;
  int opt = 0;
  int play = 0;

  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Window *screen = SDL_CreateWindow("Silly Dying Larry", 0, 0, screen_w, 
                                        screen_h, SDL_WINDOW_OPENGL);


  SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1,
                                              SDL_RENDERER_ACCELERATED
                                              | SDL_RENDERER_PRESENTVSYNC
                                              | SDL_RENDERER_TARGETTEXTURE);

  // music

  Mix_Music *music = NULL;
  //int playmusic = 1;
  //int pausemusic = 0;

  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

  music = Mix_LoadMUS("music/menumusic.mp3");

  if (Mix_PlayingMusic() == 0)
    Mix_PlayMusic(music, 0);

  // end of music

  SDL_Surface *background = IMG_Load("images/menu.png");

  SDL_Surface *buttonpo = IMG_Load("images/ButtonSelectOn.png");
  SDL_Surface *buttonpf = IMG_Load("images/ButtonSelectOff.png");
  SDL_Surface *buttonoo = IMG_Load("images/ButtonOptionsOn.png");
  SDL_Surface *buttonof = IMG_Load("images/ButtonOptionsOff.png");
  SDL_Surface *buttonqo = IMG_Load("images/ButtonQuitOn.png");
  SDL_Surface *buttonqf = IMG_Load("images/ButtonQuitOff.png");

  SDL_Texture *backtex = SDL_CreateTextureFromSurface(renderer, background);

  SDL_Texture *btexpo = SDL_CreateTextureFromSurface(renderer, buttonpo);
  SDL_Texture *btexpf = SDL_CreateTextureFromSurface(renderer, buttonpf);
  SDL_Texture *btexoo = SDL_CreateTextureFromSurface(renderer, buttonoo);
  SDL_Texture *btexof = SDL_CreateTextureFromSurface(renderer, buttonof);
  SDL_Texture *btexqo = SDL_CreateTextureFromSurface(renderer, buttonqo);
  SDL_Texture *btexqf = SDL_CreateTextureFromSurface(renderer, buttonqf);

  SDL_FreeSurface(buttonpo);
  SDL_FreeSurface(buttonpf);
  SDL_FreeSurface(buttonoo);
  SDL_FreeSurface(buttonof);
  SDL_FreeSurface(buttonqo);
  SDL_FreeSurface(buttonqf);

  SDL_RenderClear(renderer);

  SDL_Rect rectplay;
  rectplay.w = screen_w / 5;
  rectplay.h = screen_h / 12;
  rectplay.x = (screen_w / 2) - (rectplay.w / 2);
  rectplay.y = screen_h / 2;

  SDL_Rect rectoptions;
  rectoptions.w = screen_w / 5;
  rectoptions.h = screen_h / 12;
  rectoptions.x = (screen_w / 2) - (rectoptions.w / 2);
  rectoptions.y = screen_h / 2 + (rectoptions.h * 2);

  SDL_Rect rectquit;
  rectquit.w = screen_w / 5;
  rectquit.h = screen_h / 12;
  rectquit.x = (screen_w / 2) - (rectquit.w / 2);
  rectquit.y = screen_h / 2 + (rectquit.h * 4);

  SDL_RenderCopy(renderer, backtex, NULL, NULL);

  SDL_RenderCopy(renderer, btexpo, NULL, &rectplay);
  SDL_RenderCopy(renderer, btexof, NULL, &rectoptions);
  SDL_RenderCopy(renderer, btexqf, NULL, &rectquit);

  int whichbutton = 0;

  SDL_RenderPresent(renderer);

  while (end == 0)
  {
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {

    }

    const Uint8 *keystates = SDL_GetKeyboardState(NULL);

    Uint8 up = keystates[SDL_SCANCODE_UP];
    Uint8 down = keystates[SDL_SCANCODE_DOWN];

    Uint8 escape = keystates[SDL_SCANCODE_ESCAPE];
    Uint8 enter = keystates[SDL_SCANCODE_KP_ENTER];

    if (escape)
      end = 1;

    if (whichbutton == 2 && enter)
      end = 1;

    if (whichbutton == 1 && enter)
    {
      opt = 1;
      end = 1;
    }

    if (whichbutton == 0 && enter)
    {
      play = 1;
      end = 1;
    }

    if (up)
      whichbutton--;

    else if (down)
      whichbutton++;

    if (whichbutton == 3)
      whichbutton--;

    if (whichbutton == -1)
      whichbutton++;

    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, backtex, NULL, NULL);

    if (whichbutton == 0)
    {
      SDL_RenderCopy(renderer, btexpo, NULL, &rectplay);
      SDL_RenderCopy(renderer, btexof, NULL, &rectoptions);
      SDL_RenderCopy(renderer, btexqf, NULL, &rectquit);
    }

    else if (whichbutton == 1)
    {
      SDL_RenderCopy(renderer, btexpf, NULL, &rectplay);
      SDL_RenderCopy(renderer, btexoo, NULL, &rectoptions);
      SDL_RenderCopy(renderer, btexqf, NULL, &rectquit);
    }

    else if (whichbutton == 2)
    {
      SDL_RenderCopy(renderer, btexpf, NULL, &rectplay);
      SDL_RenderCopy(renderer, btexof, NULL, &rectoptions);
      SDL_RenderCopy(renderer, btexqo, NULL, &rectquit);
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(110);
  }

  if (background)
    SDL_FreeSurface(background);

  if (opt == 1)
    return 1;

  if (play == 1)
    return 0;

  return -1;
}
