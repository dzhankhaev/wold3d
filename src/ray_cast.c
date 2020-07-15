#include "wolf3d.h"

/*
 * Бросит луч. Вернет его длину, номер текстуры и координату столкновения
 */
static t_ray	find_ray_length(t_pl player, const char *map, int map_width)
{
	double	c;
	t_ray	ray;
	double	x;
	double	y;

	c = 0;
	x = player.x;
	y = player.y;
	while (!(map[(int)x + (int)y * map_width] >= '1' &&
	map[(int)x + (int)y * map_width] <= '9'))
	{
		x = player.x + c * cos(player.direction);
		y = player.y + c * sin(player.direction);
		c += RAY_STEP;
	}
	ray.ntex = map[(int)x + (int)y * map_width];
	ray.x = x;
	ray.y = y;
	ray.length = c;
	return (ray);
}

t_ray	*ray_cast(int win_width, t_point map_size,
				   char *map, t_pl player)
{
	t_ray	*ray;
	int		i;
	double	t;

	if (!(ray = (t_ray *)malloc(sizeof(t_ray) * win_width)))
		print_error_and_close_app(__FILE__, __FUNCTION__, __LINE__);
	i = 0;
	while (i < win_width)
	{
		t = player.direction;
		player.direction = (player.direction - (double)(player.fov) / 2) +
						   ((double)(player.fov * i) / win_width);
		ray[i] = find_ray_length(player, map, map_size.x);
		ray[i].angle = t - player.direction;
		player.direction = t;
		i++;
	}
	return (ray);
}