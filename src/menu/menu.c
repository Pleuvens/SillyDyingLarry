//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "../structure.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1152; //1152 - 1280
const int SCREEN_HEIGHT = 960;  //960 - 1024
const int SCREEN_BPP = 32;

// The main screen
SDL_Window *window = NULL;
    
SDL_Event event = NULL;

//for resize
SDL_Renderer *menu_renderer = NULL;
SDL_Texture *menutex = NULL;

int initialisation(void)
{
  int res = 0;

  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    printf("SDL initialisation, Error: %s\n", SDL_GetError());
    res = 1;
  }
  else
  {
    //Create window
    window = SDL_CreateWindow("Silly Dying Larry", 0, 0, SCREEN_WIDTH, 
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if( window == NULL )
    {
      printf("Window creation, Error: %s\n", SDL_GetError());
      res = 1;
    }
    else
    {
      //Get window surface
      screenSurface = SDL_GetWindowSurface(window);
    }
  }
  menu_renderer = SDL_CreateRenderer(window, -1,
                                              SDL_RENDERER_ACCELERATED
                                              | SDL_RENDERER_PRESENTVSYNC
                                              | SDL_RENDERER_TARGETTEXTURE);

  return res;
}


int load_apply_image_menu(void)
{
  SDL_RenderClear(menu_renderer);

	int res = 0;

	//Load splash image
	menu = IMG_Load("../../images/menu.png");

  menutex = SDL_CreateTextureFromSurface(menu_renderer, menu);

  SDL_RenderCopy(menu_renderer, menutex, NULL, NULL);


	if(menu == NULL)
	{
		printf("Can't load image, Error: %s\n", SDL_GetError());
		res = 1;
	}

  SDL_RenderPresent(menu_renderer);

	return res;
}


void quit_and_free(void)
{
	//Deallocate surface
	SDL_FreeSurface(menu);
	menu = NULL;

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}


int main(void)
{
  //Start up SDL and create window
  if(initialisation() == 1)
  {
    printf("Fail initialisation\n");
    return 1;
  }
  else
  {
    //Load media
    if(load_apply_image_menu() == 1)
    {
      printf("Fail image\n");
      return 1;
    }
    else
    {
      //Apply the image
      //SDL_BlitSurface(menu, NULL, screenSurface, NULL);

      //Update the surface
      //SDL_UpdateWindowSurface(window);

      //Wait two seconds
      SDL_Delay(5000);
    }
  }

  //Free resources and close SDL
  quit_and_free();

  return 0;
}
