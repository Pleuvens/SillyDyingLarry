#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

#include "../structures.h"

struct level *init_level(SDL_Renderer *renderer)
{
  struct level *l = malloc(sizeof(struct level));

  SDL_Surface *background = IMG_Load("images/menu.png");

  SDL_Surface *button1l = IMG_Load("images/Level1lock.png");
  SDL_Surface *button2l = IMG_Load("images/Level2lock.png");
  SDL_Surface *button3l = IMG_Load("images/Level3lock.png");
  SDL_Surface *button4l = IMG_Load("images/Level4lock.png");
  SDL_Surface *button5l = IMG_Load("images/Level5lock.png");

  SDL_Surface *button1o = IMG_Load("images/Level1On.png");
  SDL_Surface *button2o = IMG_Load("images/Level2On.png");
  SDL_Surface *button3o = IMG_Load("images/Level3On.png");
  SDL_Surface *button4o = IMG_Load("images/Level4On.png");
  SDL_Surface *button5o = IMG_Load("images/Level5On.png");

  SDL_Surface *button1f = IMG_Load("images/Level1Off.png");
  SDL_Surface *button2f = IMG_Load("images/Level2Off.png");
  SDL_Surface *button3f = IMG_Load("images/Level3Off.png");
  SDL_Surface *button4f = IMG_Load("images/Level4Off.png");
  SDL_Surface *button5f = IMG_Load("images/Level5Off.png");

  l->backtex = SDL_CreateTextureFromSurface(renderer, background);

  l->btex1l = SDL_CreateTextureFromSurface(renderer, button1l);
  l->btex2l = SDL_CreateTextureFromSurface(renderer, button2l);
  l->btex3l = SDL_CreateTextureFromSurface(renderer, button3l);
  l->btex4l = SDL_CreateTextureFromSurface(renderer, button4l);
  l->btex5l = SDL_CreateTextureFromSurface(renderer, button5l);

  l->btex1o = SDL_CreateTextureFromSurface(renderer, button1o);
  l->btex2o = SDL_CreateTextureFromSurface(renderer, button2o);
  l->btex3o = SDL_CreateTextureFromSurface(renderer, button3o);
  l->btex4o = SDL_CreateTextureFromSurface(renderer, button4o);
  l->btex5o = SDL_CreateTextureFromSurface(renderer, button5o);

  l->btex1f = SDL_CreateTextureFromSurface(renderer, button1f);
  l->btex2f = SDL_CreateTextureFromSurface(renderer, button2f);
  l->btex3f = SDL_CreateTextureFromSurface(renderer, button3f);
  l->btex4f = SDL_CreateTextureFromSurface(renderer, button4f);
  l->btex5f = SDL_CreateTextureFromSurface(renderer, button5f);

  SDL_FreeSurface(background);

  SDL_FreeSurface(button1l);
  SDL_FreeSurface(button2l);
  SDL_FreeSurface(button3l);
  SDL_FreeSurface(button4l);
  SDL_FreeSurface(button5l);

  SDL_FreeSurface(button1o);
  SDL_FreeSurface(button2o);
  SDL_FreeSurface(button3o);
  SDL_FreeSurface(button4o);
  SDL_FreeSurface(button5o);

  SDL_FreeSurface(button1f);
  SDL_FreeSurface(button2f);
  SDL_FreeSurface(button3f);
  SDL_FreeSurface(button4f);
  SDL_FreeSurface(button5f);

  return l;
}

SDL_Rect init_rectl(int w, int h, int cpt)
{
  SDL_Rect rect;

  rect.w = w / 5;
  rect.h = h / 12;
  rect.x = (w / 2) - (rect.w / 2);
  rect.y = h / 2 - (h / 4)  + (rect.h * cpt);

  return rect;
}

void destroy_level(SDL_Window *w, SDL_Renderer *r, struct level *l)
{
  if (l)
  {
    SDL_DestroyTexture(l->backtex);
    SDL_DestroyTexture(l->btex1l);
    SDL_DestroyTexture(l->btex2l);
    SDL_DestroyTexture(l->btex3l);
    SDL_DestroyTexture(l->btex4l);
    SDL_DestroyTexture(l->btex5l);
    SDL_DestroyTexture(l->btex1o);
    SDL_DestroyTexture(l->btex2o);
    SDL_DestroyTexture(l->btex3o);
    SDL_DestroyTexture(l->btex4o);
    SDL_DestroyTexture(l->btex5o);
    SDL_DestroyTexture(l->btex1f);
    SDL_DestroyTexture(l->btex2f);
    SDL_DestroyTexture(l->btex3f);
    SDL_DestroyTexture(l->btex4f);
    SDL_DestroyTexture(l->btex5f);

    free(l);
  }

  if (r)
    SDL_DestroyRenderer(r);

  if (w)
    SDL_DestroyWindow(w);
}

int onclickl(SDL_Rect r1, SDL_Rect r2, SDL_Rect r3, SDL_Rect r4, SDL_Rect r5)
{
  int x = 0;
  int y = 0;

  SDL_GetMouseState(&x, &y);

  if (x > r1.x && x < (r1.x + r1.w))
  {
    if (y >r1.y && y < (r1.y + r1.h))
      return 1;

    if (y >r2.y && y < (r2.y + r2.h))
      return 2;

    if (y >r3.y && y < (r3.y + r3.h))
      return 3;

    if (y >r4.y && y < (r4.y + r4.h))
      return 4;

    if (y >r5.y && y < (r5.y + r5.h))
      return 5;
  }

  return 0;
}

int level_selection(int screen_w, int screen_h, struct current_level *cl)
{
  int end = 0;
  int thislevel = 0;

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

  struct level *l = init_level(renderer);

  SDL_RenderClear(renderer);

  SDL_Rect rect1 = init_rectl(screen_w, screen_h, 0);
  SDL_Rect rect2 = init_rectl(screen_w, screen_h, 2);
  SDL_Rect rect3 = init_rectl(screen_w, screen_h, 4);
  SDL_Rect rect4 = init_rectl(screen_w, screen_h, 6);
  SDL_Rect rect5 = init_rectl(screen_w, screen_h, 8);

  SDL_RenderCopy(renderer, l->backtex, NULL, NULL);

  SDL_RenderCopy(renderer, l->btex1o, NULL, &rect1);

  if (cl->lvl2 == 1)
  {
    SDL_RenderCopy(renderer, l->btex2f, NULL, &rect2);
  }
  else
    SDL_RenderCopy(renderer, l->btex2l, NULL, &rect2);

  if (cl->lvl3 == 1)
  {
    SDL_RenderCopy(renderer, l->btex3f, NULL, &rect3);
  }
  else
    SDL_RenderCopy(renderer, l->btex3l, NULL, &rect3);

  if (cl->lvl4 == 1)
  {
    SDL_RenderCopy(renderer, l->btex4f, NULL, &rect4);
  }
  else
    SDL_RenderCopy(renderer, l->btex4l, NULL, &rect4);

  if (cl->lvl5 == 1)
  {
    SDL_RenderCopy(renderer, l->btex5f, NULL, &rect5);
  }
  else
    SDL_RenderCopy(renderer, l->btex5l, NULL, &rect5);

  int whichbutton = 1;
  int click = 0;

  SDL_RenderPresent(renderer);

  while (end == 0)
  {
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_MOUSEBUTTONDOWN)
      {
        click = onclickl(rect1, rect2, rect3, rect4, rect5);
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

    if ((whichbutton == 1 && (enter || enter2)) || (click == 1 && 
         click <= cl->lim))
    {
      thislevel = 1;
      end = 1;
    }

    if ((whichbutton == 2 && (enter || enter2)) || (click == 2 &&
         click <= cl->lim))
    {
      thislevel = 2;
      end = 1;
    }

    if ((whichbutton == 3 && (enter || enter2)) || (click == 3 &&
         click <= cl->lim))
    {
      thislevel = 3;
      end = 1;
    }

    if ((whichbutton == 4 && (enter || enter2)) || (click == 4 &&
         click <= cl->lim))
    {
      thislevel = 4;
      end = 1;
    }

    if ((whichbutton == 5 && (enter || enter2)) || (click == 5 &&
         click <= cl->lim))
    {
      thislevel = 5;
      end = 1;
    }

    if (up)
      whichbutton--;

    else if (down)
      whichbutton++;

    if (whichbutton == (cl->lim + 1))
      whichbutton--;

    if (whichbutton == 0)
      whichbutton++;

    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, l->backtex, NULL, NULL);

    if (cl->lvl1 == 1)
      SDL_RenderCopy(renderer, l->btex1f, NULL, &rect1);
    else
      SDL_RenderCopy(renderer, l->btex1l, NULL, &rect1);

    if (cl->lvl2 == 1)
      SDL_RenderCopy(renderer, l->btex2f, NULL, &rect2);
    else
      SDL_RenderCopy(renderer, l->btex2l, NULL, &rect2);

    if (cl->lvl3 == 1)
      SDL_RenderCopy(renderer, l->btex3f, NULL, &rect3);
    else
      SDL_RenderCopy(renderer, l->btex3l, NULL, &rect3);

    if (cl->lvl4 == 1)
      SDL_RenderCopy(renderer, l->btex4f, NULL, &rect4);
    else
      SDL_RenderCopy(renderer, l->btex4l, NULL, &rect4);

    if (cl->lvl5 == 1)
      SDL_RenderCopy(renderer, l->btex5f, NULL, &rect5);
    else
      SDL_RenderCopy(renderer, l->btex5l, NULL, &rect5);



    if (whichbutton == 1)
      SDL_RenderCopy(renderer, l->btex1o, NULL, &rect1);

    else if (whichbutton == 2)
      SDL_RenderCopy(renderer, l->btex2o, NULL, &rect1);

    else if (whichbutton == 3)
      SDL_RenderCopy(renderer, l->btex3o, NULL, &rect3);

    else if (whichbutton == 4)
      SDL_RenderCopy(renderer, l->btex4o, NULL, &rect4);

    else if (whichbutton == 5)
      SDL_RenderCopy(renderer, l->btex5o, NULL, &rect5);

    SDL_RenderPresent(renderer);

    SDL_Delay(110);
  }

  destroy_level(screen, renderer, l);

  return thislevel;
}
