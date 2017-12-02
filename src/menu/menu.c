//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 608;

//The window we'll be rendering to
SDL_Window* window = NULL;
    
//The surface contained by the window
SDL_Surface* screenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* test = NULL;

int initialisation(void)
{
  int res = 0;

  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    printf("SDL initialisation, Error: %s\n", SDL_GetError());
  }
  else
  {
    //Create window
    window = SDL_CreateWindow("Silly Dying Larry", 0, 0, SCREEN_WIDTH, 
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if( window == NULL )
    {
      printf("Window creation, Error: %s\n", SDL_GetError());
    }
    else
    {
      //Get window surface
      screenSurface = SDL_GetWindowSurface(window);
    }
  }

  return res;
}

int load_image(void)
{
	int res = true;

	//Load splash image
	test = SDL_LoadBMP( "02_getting_an_image_on_the_screen/hello_world.bmp" );
	if( gHelloWorld == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
		success = false;
	}

	return res;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface( gHelloWorld );
	gHelloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main(void)
{



      //Fill the surface white
      SDL_FillRect(screenSurface, NULL, 
                   SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
            
      //Update the surface
      SDL_UpdateWindowSurface(window);

      //Wait two seconds
      SDL_Delay(2000);
    }
  }
  //Destroy window
  SDL_DestroyWindow(window);

  //Quit SDL subsystems
  SDL_Quit();
  close();
  return 0;
}
