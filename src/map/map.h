#ifndef MAP_H
# define MAP_H

# define TILE_WIDTH 32
# define TILE_HEIGHT 32

# include "../structures.h"

void generate_map(struct context *context);

void update_mao(struct context *context);

#endif /* !MAP_H */
