#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

#include "../structures.h"


struct button *init_button(SDL_Renderer *renderer)
{
  struct button *b = malloc(sizeof(struct button));

  SDL_Surface *background = IMG_Load("src/images/menu.png");

  SDL_Surface *buttonpo = IMG_Load("src/images/ButtonSelectOn.png");
  SDL_Surface *buttonpf = IMG_Load("src/images/ButtonSelectOff.png");
  SDL_Surface *buttonoo = IMG_Load("src/images/ButtonOptionsOn.png");
  SDL_Surface *buttonof = IMG_Load("src/images/ButtonOptionsOff.png");
  SDL_Surface *buttonqo = IMG_Load("src/images/ButtonQuitOn.png");
  SDL_Surface *buttonqf = IMG_Load("src/images/ButtonQuitOff.png");

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

void destroy_menu(SDL_Window *w, SDL_Renderer *r, struct button *b)
{
  if (b)
  {
    SDL_DestroyTexture(b->backtex);
    SDL_DestroyTexture(b->btexpo);
    SDL_DestroyTexture(b->btexpf);
    SDL_DestroyTexture(b->btexoo);
    SDL_DestroyTexture(b->btexof);
    SDL_DestroyTexture(b->btexqo);
    SDL_DestroyTexture(b->btexqf);

    free(b);
  }

  if (r)
    SDL_DestroyRenderer(r);

  if (w)
    SDL_DestroyWindow(w);
}

int onclick(SDL_Rect rp, SDL_Rect ro, SDL_Rect rq)
{
  int x = 0;
  int y = 0;

  SDL_GetMouseState(&x, &y);

  if (x > rp.x && x < (rp.x + rp.w))
  {
    if (y >rp.y && y < (rp.y + rp.h))
      return 0;

    if (y >ro.y && y < (ro.y + ro.h))
      return 1;

    if (y >rq.y && y < (rq.y + rq.h))
      return 2;
  }

  return -1;
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

  music = Mix_LoadMUS("src/music/menumusic.mp3");

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
  int click = -1;

  SDL_RenderPresent(renderer);

  while (end == 0)
  {
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_MOUSEBUTTONDOWN)
      {
        click = onclick(rectplay, rectoptions, rectquit);
      }
    }

    const Uint8 *keystates = SDL_GetKeyboardState(NULL);

    Uint8 up = keystates[SDL_SCANCODE_UP];
    Uint8 down = keystates[SDL_SCANCODE_DOWN];

    Uint8 escape = keystates[SDL_SCANCODE_ESCAPE];
    Uint8 enter = keystates[SDL_SCANCODE_KP_ENTER];
    Uint8 enter2 = keystates[SDL_SCANCODE_RETURN];

    if (escape)
      end = 1;

    if ((whichbutton == 2 && (enter || enter2)) || click == 2)
      end = 1;

    if ((whichbutton == 1 && (enter || enter2)) || click == 1)
    {
      opt = 1;
      end = 1;
    }

    if ((whichbutton == 0 && (enter || enter2)) || click == 0)
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

  destroy_menu(screen, renderer, b);

  if (opt == 1)
    return 1;

  if (play == 1)
    return 0;

  return -1;
}
