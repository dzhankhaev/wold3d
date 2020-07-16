#include "wolf3d.h"

/*
 * Определит направление участка стены. 1 - север, 2 - юг, 3 - запад, 4 - восток
 */
static char		wall_direction(char *map, double x, double y, int map_width)
{
	if (map[(int)x + (int)(y - RAY_STEP) * map_width] == ' ')
		return ('1');
	else if (map[(int)x + (int)(y + RAY_STEP) * map_width] == ' ')
		return ('2');
	else if (map[(int)(x - RAY_STEP) + (int)y * map_width] == ' ')
		return ('3');
	else if (map[(int)(x + RAY_STEP) + (int)y * map_width] == ' ')
		return ('4');
	return (0);
}

/*
 * Бросит луч. Вернет его длину, номер текстуры и координату столкновения
 */
static t_ray	find_ray_length(double *length, t_pl player, char *map,
		int map_width)
{
	t_ray	ray;
	double	x;
	double	y;

	*length = 0;
	x = player.x;
	y = player.y;
	while (!(map[(int)x + (int)y * map_width] >= '1' &&
	map[(int)x + (int)y * map_width] <= '9'))
	{
		x = player.x + *length * cos(player.direction);
		y = player.y + *length * sin(player.direction);
		*length += RAY_STEP;
	}
	ray.wall_dir = wall_direction(map, x, y, map_width);
	ray.ntex = map[(int)x + (int)y * map_width];
//раньше без этого условия сегалось, сейчас вроде нет. Надо проверить
	if (*length < 1.0)
		*length = 1.0;
	return (ray);
}

t_ray	*ray_cast(t_point win, t_point map_size,
				   char *map, t_pl player)
{
	t_ray	*ray;
	int		i;
	double	t;
	double	length;

	if (!(ray = (t_ray *)malloc(sizeof(t_ray) * win.x)))
		print_error_and_close_app(__FILE__, __FUNCTION__, __LINE__);
	i = 0;
	while (i < win.x)
	{
		t = player.direction;
		player.direction = (player.direction - (double)(player.fov) / 2) +
						   ((double)(player.fov * i) / win.x);
		ray[i] = find_ray_length(&length, player, map, map_size.x);
		ray[i].length = (int)((double)win.y /
				(length * cos(t - player.direction)));
		if (ray[i].length >= win.y)
			ray[i].length = win.y;
		player.direction = t;
		i++;
	}
	return (ray);
}