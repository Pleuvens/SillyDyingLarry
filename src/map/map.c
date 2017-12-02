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
  
  if (context->nb_enemies)
  {
    for (int i = 0; i < context->nb_enemies; ++i)
      free(context->enemies[i]);
    free(context->enemies);
    context->enemies = NULL;
  }

  context->nb_enemies = 0; 

  for (int j = 0; j < height; ++j)
  {
    for (int i = 0; i < width; ++i)
    {
      fscanf(f, "%d", map + j * width + i);
      if (map[j * width + i] == 3)
      {
        map[j * width + i] = 0;
        context->camera = calloc(1, sizeof (SDL_Rect));
        context->camera->x = i;
        context->camera->y = j;
        context->camera->w = SCREEN_WIDTH;
        context->camera->h = SCREEN_HEIGHT;
        context->player = character_create();
        context->player->pos->x = i;
        context->player->pos->y = j;
        context->player->rect.x = i;
        context->player->rect.y = j;
        context->player->rect.w = SCREEN_BPP;
        context->player->rect.h = SCREEN_BPP;
      }
      if (map[j * width + i] == 4)
      {
        context->nb_enemies += 1;
        int ie = context->nb_enemies - 1;
        context->enemies = realloc(context->enemies,
                           context->nb_enemies * sizeof (struct character *));
        context->enemies[ie] = character_create();
        context->enemies[ie]->pos->x = i;
        context->enemies[ie]->pos->y = j;
      }
    }
  }
  context->map = calloc(1, sizeof (struct map));
  context->map->width = width;
  context->map->height = height;
  context->map->type = map;
}

int is_on_screen(struct context *context, int i, int j)
{
  if (i < 0 || i >= context->map->width || j < 0 || j >= context->map->height)
    return 0;
  int infx = context->camera->x - SCREEN_WIDTH / 2;
  int supx = context->camera->x + SCREEN_WIDTH / 2;
  int infy = context->camera->y - SCREEN_HEIGHT / 2;
  int supy = context->camera->y + SCREEN_HEIGHT / 2;
  if (infx < 0)
    infx = 0;
  if (infy < 0)
    infy = 0;
  if (supx > context->map->width)
    supx = context->map->width;
  if (supy > context->map->height)
    supy = context->map->height;
  return i >= infx && i < supx && j >= infy && j < supy;
}

static void apply_texture(struct context *context, SDL_Rect dst, int i, int j)
{
  if (!is_on_screen(context, i, j))
    return;
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
  case 4:
    SDL_RenderCopy(context->renderer, context->enemytex, NULL, &dst);
    context->map->type[j * context->map->width + i] = 0;
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
      apply_texture(context, dst, i, j); 
    }
  }
}

void update_map(struct context *context)
{
  int width = context->map->width;
  int height = context->map->height;
  
  struct character *player = context->player;

  for (int ie = 0; ie < context->nb_enemies; ++ie)
  {
    struct character *enemy = context->enemies[ie];
    context->map->type[(int)enemy->pos->y * width + (int)enemy->pos->x] = 4;
  }

  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; ++j)
    {
      SDL_Rect dst =
      {
        i * 32 + context->camera->x, j * 32 + context->camera->y, 32, 32
      };
      apply_texture(context, dst, i + context->camera->x, j + context->camera->y); 
    }
  }
  
  player->rect.x = player->pos->x * SCREEN_BPP;
  player->rect.y = player->pos->y * SCREEN_BPP;
  
  SDL_RenderCopy(context->renderer, context->playertex, NULL, &(player->rect));

}
