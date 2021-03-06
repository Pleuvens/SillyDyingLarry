#include "../structures.h"
#include "../vector/vector.h"

void set_camera(struct context *context)
{
  context->camera->x = (context->player->pos->x - SCREEN_BPP / 2);// - SCREEN_WIDTH / 2;
  context->camera->y = (context->player->pos->y - SCREEN_BPP / 2);// - SCREEN_HEIGHT / 2;

  if (context->camera->x < 1)
    context->camera->x = 0;
  if (context->camera->y < 1)
    context->camera->y = 0;
  if (context->camera->x > context->map->width * SCREEN_BPP- context->camera->w / 2)
    context->camera->x = context->map->width * SCREEN_BPP- context->camera->w / 2;
  if (context->camera->y > context->map->height * SCREEN_BPP- context->camera->h / 2)
    context->camera->y = context->map->height * SCREEN_BPP- context->camera->h / 2;
}
