#include "wolf3d.h"
#include "key_defines.h"

int				key_hooks(int key, void *temp)
{
	t_mlx	*w;
	t_pl	*player;
	t_ray	*ray;
	char	*map;
	t_point	map_size;

	w = ((t_all *)temp)->w;
	player = ((t_all *)temp)->player;
	map = ((t_all *)temp)->map;
	map_size = ((t_all *)temp)->map_size;

	if (key == ESC)
		exit(0);
	else if (key == RIGHT)
	{
		if (player->direction >= 360)
			player->direction = (1 * M_PI) / 180;
		else
			player->direction += (3 * M_PI) / 180;
		ray = find_ray_length(w->width, map_size, map, *player);
		draw_image(*w, ray);
		free(ray);
	}
	else if (key == LEFT)
	{
		if (player->direction <= 0)
			player->direction = (359 * M_PI) / 180;
		else
			player->direction -= (3 * M_PI) / 180;
		ray = find_ray_length(w->width, map_size, map, *player);
		draw_image(*w, ray);
		free(ray);
	}
	/*
	else if (key == UP)
	{
		player->x += 0.2;
		ray = find_ray_length(w->width, map_size, map, *player);
		draw_image(*w, ray);
		free(ray);
	}
	else if (key == DOWN)
	{
		player->x -= 0.2;
		ray = find_ray_length(w->width, map_size, map, *player);
		draw_image(*w, ray);
		free(ray);
	}
*/
	return (0);
}