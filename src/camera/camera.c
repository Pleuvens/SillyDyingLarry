#include "../structures.h"

void set_camera(struct context *context)
{
  context->camera->x = (context->player->pos->x + TILE_SIZE / 2) - SCREEN_WIDTH / 2;
  context->camera->y = (context->player->pos->y + TILE_SIZE / 2) - SCREEN_HEIGHT / 2;

  if (context->camera->x < 0)
    context->camera->x = 0;
  if (context->camera->y < 0)
    context->camera->y = 0;
  if (context->camera->x > context->map->width - camera->w)
    context->camera->x = context->map->width - camera->w;
  if (context->camera->y > context->map->height - camera->h)
    context->camera->y = context->map->height - camera->h;
}
