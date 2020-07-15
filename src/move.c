#include "wolf3d.h"

void	player_rot(t_all *all, double rotate)
{
	t_mlx	*w;
	t_pl	*player;
	t_ray	*ray;
	char	*map;
	t_point	map_size;

	w = all->w;
	player = all->player;
	map = all->map;
	map_size = all->map_size;
	if (player->direction >= (360 * M_PI) / 180)
		player->direction = (rotate * M_PI) / 180;
	else if (player->direction <= 0)
		player->direction = ((360 + rotate) * M_PI) / 180;
	else
		player->direction += (rotate * M_PI) / 180;
	ray = find_ray_length(w->width, map_size, map, *player);
	draw_image(*w, ray);
	free(ray);
}

void	player_step(t_all *all, double step)
{
	t_mlx	*w;
	t_pl	*player;
	t_ray	*ray;
	char	*map;
	t_point	map_size;

	w = all->w;
	player = all->player;
	map = all->map;
	map_size = all->map_size;
	player->x += step * cos(player->direction);
	player->y += step * sin(player->direction);
	ray = find_ray_length(w->width, map_size, map, *player);
	draw_image(*w, ray);
	free(ray);
}