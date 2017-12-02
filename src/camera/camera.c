#include "../structures.h"
#include "../vector/vector.h"

void set_camera(struct context *context)
{
  context->camera->x = (context->player->pos->x - SCREEN_BPP / 2);// - SCREEN_WIDTH / 2;
  context->camera->y = (context->player->pos->y - SCREEN_BPP / 2);// - SCREEN_HEIGHT / 2;

  if (context->camera->x < 0)
    context->camera->x = 0;
  if (context->camera->y < 0)
    context->camera->y = 0;
  if (context->camera->x > context->map->width - context->camera->w / (2 * SCREEN_BPP))
    context->camera->x = context->map->width - context->camera->w / (2 * SCREEN_BPP);
  if (context->camera->y > context->map->height - context->camera->h / (2 * SCREEN_BPP))
    context->camera->y = context->map->height - context->camera->h / (2 * SCREEN_BPP);
}
