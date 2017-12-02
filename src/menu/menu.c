#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "../structures.h"

int main(void)
{
  int end = 0;

  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Window *screen = SDL_CreateWindow("Silly Dying Larry", 0, 0,
                          SCREEN_WIDTH, SCREEN_HEIGHT,
                          SDL_WINDOW_OPENGL);


  SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1,
                                              SDL_RENDERER_ACCELERATED
                                              | SDL_RENDERER_PRESENTVSYNC
                                              | SDL_RENDERER_TARGETTEXTURE);

  SDL_Surface *background = IMG_Load("../../images/menu.png");

  SDL_Surface *buttonpo = IMG_Load("../../images/ButtonSelectOn.png");
  SDL_Surface *buttonpf = IMG_Load("../../images/ButtonSelectOn.png");
  SDL_Surface *buttonoo = IMG_Load("../../images/ButtonOptionsOn.png");
  SDL_Surface *buttonof = IMG_Load("../../images/ButtonOptionsOff.png");
  SDL_Surface *buttonqo = IMG_Load("../../images/ButtonQuitOn.png");
  SDL_Surface *buttonqf = IMG_Load("../../images/ButtonQuitOff.png");

  SDL_Texture *backtex = SDL_CreateTextureFromSurface(renderer, background);

  SDL_Texture *btexpo = SDL_CreateTextureFromSurface(renderer, buttonpo);
  SDL_Texture *btexpf = SDL_CreateTextureFromSurface(renderer, buttonpf);
  SDL_Texture *btexoo = SDL_CreateTextureFromSurface(renderer, buttonoo);
  SDL_Texture *btexof = SDL_CreateTextureFromSurface(renderer, buttonof);
  SDL_Texture *btexqo = SDL_CreateTextureFromSurface(renderer, buttonqo);
  SDL_Texture *btexqf = SDL_CreateTextureFromSurface(renderer, buttonqf);

  SDL_RenderClear(renderer);

  SDL_Rect rectplay;
  rectplay.w = SCREEN_WIDTH / 13;
  rectplay.h = SCREEN_HEIGHT / 13;
  rectplay.x = (SCREEN_WIDTH / 2) - (rectplay.w / 2);
  rectplay.y = SCREEN_HEIGHT / 2;

  SDL_Rect rectoptions;
  rectoptions.w = SCREEN_WIDTH / 13;
  rectoptions.h = SCREEN_HEIGHT / 13;
  rectoptions.x = (SCREEN_WIDTH / 2) - (rectoptions.w / 2);
  rectoptions.y = SCREEN_HEIGHT / 2 - (rectoptions.w * 2);

  SDL_Rect rectquit;
  rectquit.w = SCREEN_WIDTH / 13;
  rectquit.h = SCREEN_HEIGHT / 13;
  rectquit.x = (SCREEN_WIDTH / 2) - (rectquit.w / 2);
  rectquit.y = SCREEN_HEIGHT / 2 - (rectquit.w * 4);

  SDL_RenderCopy(renderer, backtex, NULL, NULL);

  SDL_RenderCopy(renderer, btexpo, NULL, &rectplay);
  SDL_RenderCopy(renderer, btexof, NULL, &rectoptions);
  SDL_RenderCopy(renderer, buttqf, NULL, &rectquit);

  int whichbutton = 0;

  SDL_RenderPresent(renderer);

  while (end == 0)
  {
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
      {
        end = 0;
        break;
      }
    }

    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    Uint8 escape = keystates[SDL_SCANCODE_ESCAPE];
    Uint8 up = keystates[SDL_SCANCODE_UP];
    Uint8 down = keystates[SDL_SCANCODE_DOWN];

    if (escape)
      end = 1;

    if (up)
      whichbutton--;

    else if (down)
      whichbutton++;

    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, backtex, NULL, NULL);

    if (wichbutton == 0)
    {
      SDL_RenderCopy(renderer, btexpo, NULL, &rectplay);
      SDL_RenderCopy(renderer, btexof, NULL, &rectoptions);
      SDL_RenderCopy(renderer, buttqf, NULL, &rectquit);
    }

    else if (wichbutton == 1)
    {
      SDL_RenderCopy(renderer, btexpf, NULL, &rectplay);
      SDL_RenderCopy(renderer, btexoo, NULL, &rectoptions);
      SDL_RenderCopy(renderer, buttqf, NULL, &rectquit);
    }

    else if (wichbutton == 2)
    {
      SDL_RenderCopy(renderer, btexpf, NULL, &rectplay);
      SDL_RenderCopy(renderer, btexof, NULL, &rectoptions);
      SDL_RenderCopy(renderer, buttqo, NULL, &rectquit);
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(50);
  }

  if (background)
    SDL_FreeSurface(background);

  if (button)
    SDL_FreeSurface(button);

  return 0;
}
