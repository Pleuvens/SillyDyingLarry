#include "../main/main.h"
#include "map.h"
#include "../vector/vector.h"
#include "../character/character.h"
#include "../camera/camera.h"

static void parse_file(struct context *context, char *path)
{
  int width = 0;
  int height = 0;
  
  FILE *f = fopen(path, "r");
  
  fscanf(f, "%d %d", &width, &height);

  int *map = calloc(width * height, sizeof (int));

  for (int i = 0; i < width; ++i)
  {
    for (int j = 0; j < height; ++j)
    {
      fscanf(f, "%d", map + i * height + j);
      if (map[i * height + j] == 3)
      {
        SDL_Rect c =
        {
          i, j, SCREEN_WIDTH, SCREEN_HEIGHT
        };
        context->camera = &c;
        context->player = character_create();
        context->player->pos->x = i;
        context->player->pos->y = j;
      }
    }
  }
  context->map = calloc(1, sizeof (struct map));
  context->map->width = width;
  context->map->height = height;
  context->map->type = map;
}

static void apply_texture_init(struct context *context, SDL_Rect dst, int i,
                               int j)
{
  switch (context->map->type[j * context->map->width + i])
  {
  case 0:
    SDL_RenderCopy(context->renderer, context->backtex, NULL, &dst);
    break;
  case 1:
    SDL_RenderCopy(context->renderer, context->groundtex, NULL, &dst);
    break;
  case 2:
    SDL_RenderCopy(context->renderer, context->watertex, NULL, &dst);
    break;
  case 3:
    SDL_RenderCopy(context->renderer, context->playertex, NULL, &dst);
    context->map->type[j * context->map->width + i] = 0; 
    break;
  default:
    break;
  }
}

static void apply_texture(struct context *context, SDL_Rect dst, int i, int j)
{
  switch (context->map->type[j * context->map->width + i])
  {
  case 0:
    SDL_RenderCopy(context->renderer, context->backtex, NULL, &dst);
    break;
  case 1:
    SDL_RenderCopy(context->renderer, context->groundtex, NULL, &dst);
    break;
  case 2:
    SDL_RenderCopy(context->renderer, context->watertex, NULL, &dst);
    break;
  case 3:
    SDL_RenderCopy(context->renderer, context->playertex, NULL, &dst);
    context->map->type[j * context->map->width + i] = context->player->previous_tile;
    break;
  default:
    break;
  }
}

static void load_textures(struct context *context)
{
  SDL_Surface *backsurf = IMG_Load("images/background_tile.png");
  SDL_Surface *groundsurf = IMG_Load("images/ground.png");
  SDL_Surface *playersurf = IMG_Load("images/player.png");
  SDL_Surface *watersurf = IMG_Load("images/water.png");
  SDL_Surface *enemysurf = IMG_Load("images/enemy.png");
  context->backtex = SDL_CreateTextureFromSurface(context->renderer,
                                                       backsurf);
  context->groundtex = SDL_CreateTextureFromSurface(context->renderer,
                                                       groundsurf);
  context->playertex = SDL_CreateTextureFromSurface(context->renderer,
                                                       playersurf);
  context->watertex = SDL_CreateTextureFromSurface(context->renderer,
                                                       watersurf);
  context->enemytex = SDL_CreateTextureFromSurface(context->renderer,
                                                      enemysurf);
  SDL_FreeSurface(backsurf);
  SDL_FreeSurface(groundsurf);
  SDL_FreeSurface(playersurf);
  SDL_FreeSurface(watersurf);
  SDL_FreeSurface(enemysurf);
}

void generate_map(struct context *context)
{
  load_textures(context); 
  parse_file(context, "maps/level1.map");

  int width = context->map->width;
  int height = context->map->height;

  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; ++j)
    {
      SDL_Rect dst =
      {
        i * 32, j * 32, 32, 32
      };
      apply_texture_init(context, dst, i, j); 
    }
  }
}

void update_map(struct context *context)
{
  int width = context->map->width;
  int height = context->map->height;
  
  struct character *player = context->player;

  context->map->type[(int)player->pos->y * width + (int)player->pos->x] = 3;

  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; ++j)
    {
      SDL_Rect dst =
      {
        i * 32, j * 32, 32, 32
      };
      apply_texture(context, dst, i, j); 
    }
  }
}
