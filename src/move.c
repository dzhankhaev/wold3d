#include "wolf3d.h"

void		player_rot(t_all *all, double rotate)
{
	t_mlx	*w;
	t_pl	*player;
	t_ray	*ray;
	char	*map;
	t_point	map_size;
	t_point	win;

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
	win.x = w->width;
	win.y = w->height;
	ray = ray_cast(win, map_size, map, *player);
	draw_image(*w, ray);
	free(ray);
}

static int	check_collision(const char *map, int map_width, double x, double y)
{
	if (!(map[(int)x + (int)y * map_width] >= '1' &&
			 map[(int)x + (int)y * map_width] <= '9'))
		return (1);
	return (0);
}

void		player_step(t_all *all, double step)
{
	t_mlx	*w;
	t_pl	*player;
	t_ray	*ray;
	char	*map;
	t_point	map_size;
	double	x;
	double	y;
	t_point	win;

	w = all->w;
	player = all->player;
	map = all->map;
	map_size = all->map_size;
	x = player->x;
	y = player->y;
	player->x += step * cos(player->direction);
	player->y += step * sin(player->direction);
	if (check_collision(map, map_size.x, player->x, player->y))
	{
		win.x = w->width;
		win.y = w->height;
		ray = ray_cast(win, map_size, map, *player);
		draw_image(*w, ray);
		free(ray);
		return ;
	}
	player->x = x;
	player->y = y;
}