#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

#include "../structures.h"


struct button *init_button(SDL_Renderer *renderer)
{
  struct button *b = malloc(sizeof(struct button));

  SDL_Surface *background = IMG_Load("images/menu.png");

  SDL_Surface *buttonpo = IMG_Load("images/ButtonSelectOn.png");
  SDL_Surface *buttonpf = IMG_Load("images/ButtonSelectOff.png");
  SDL_Surface *buttonoo = IMG_Load("images/ButtonOptionsOn.png");
  SDL_Surface *buttonof = IMG_Load("images/ButtonOptionsOff.png");
  SDL_Surface *buttonqo = IMG_Load("images/ButtonQuitOn.png");
  SDL_Surface *buttonqf = IMG_Load("images/ButtonQuitOff.png");

  b->backtex = SDL_CreateTextureFromSurface(renderer, background);

  b->btexpo = SDL_CreateTextureFromSurface(renderer, buttonpo);
  b->btexpf = SDL_CreateTextureFromSurface(renderer, buttonpf);
  b->btexoo = SDL_CreateTextureFromSurface(renderer, buttonoo);
  b->btexof = SDL_CreateTextureFromSurface(renderer, buttonof);
  b->btexqo = SDL_CreateTextureFromSurface(renderer, buttonqo);
  b->btexqf = SDL_CreateTextureFromSurface(renderer, buttonqf);

  SDL_FreeSurface(buttonpo);
  SDL_FreeSurface(buttonpf);
  SDL_FreeSurface(buttonoo);
  SDL_FreeSurface(buttonof);
  SDL_FreeSurface(buttonqo);
  SDL_FreeSurface(buttonqf);

  return b;
}

SDL_Rect init_rect(int w, int h, int cpt)
{
  SDL_Rect rect;

  rect.w = w / 5;
  rect.h = h / 12;
  rect.x = (w / 2) - (rect.w / 2);
  rect.y = h / 2 + (rect.h * cpt);

  return rect;
}


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

  struct button *b = init_button(renderer);

  SDL_RenderClear(renderer);

  SDL_Rect rectplay = init_rect(screen_w, screen_h, 0);
  SDL_Rect rectoptions = init_rect(screen_w, screen_h, 2);
  SDL_Rect rectquit = init_rect(screen_w, screen_h, 4);

  SDL_RenderCopy(renderer, b->backtex, NULL, NULL);

  SDL_RenderCopy(renderer, b->btexpo, NULL, &rectplay);
  SDL_RenderCopy(renderer, b->btexof, NULL, &rectoptions);
  SDL_RenderCopy(renderer, b->btexqf, NULL, &rectquit);

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

    SDL_RenderCopy(renderer, b->backtex, NULL, NULL);

    if (whichbutton == 0)
    {
      SDL_RenderCopy(renderer, b->btexpo, NULL, &rectplay);
      SDL_RenderCopy(renderer, b->btexof, NULL, &rectoptions);
      SDL_RenderCopy(renderer, b->btexqf, NULL, &rectquit);
    }

    else if (whichbutton == 1)
    {
      SDL_RenderCopy(renderer, b->btexpf, NULL, &rectplay);
      SDL_RenderCopy(renderer, b->btexoo, NULL, &rectoptions);
      SDL_RenderCopy(renderer, b->btexqf, NULL, &rectquit);
    }

    else if (whichbutton == 2)
    {
      SDL_RenderCopy(renderer, b->btexpf, NULL, &rectplay);
      SDL_RenderCopy(renderer, b->btexof, NULL, &rectoptions);
      SDL_RenderCopy(renderer, b->btexqo, NULL, &rectquit);
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(110);
  }

  if (opt == 1)
    return 1;

  if (play == 1)
    return 0;

  return -1;
}
