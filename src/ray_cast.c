#include "wolf3d.h"

/*
 * Определит направление участка стены. 1 - север, 2 - юг, 3 - запад, 4 - восток
 */
/* не работает
static char		wall_direction(char *map, double x, double y, int map_width)
{
	if (x <= 0.9999)
		x = 1;
	if (y <= 0.9999)
		y = 1;
	if (map[(int)x + (int)(y - 0.1) * map_width] == ' ')
		return ('1');
	else if (map[(int)x + (int)(y + 0.1) * map_width] == ' ')
		return ('2');
	else if (map[(int)(x - 0.1) + (int)y * map_width] == ' ')
		return ('3');
	else if (map[(int)(x + 0.1) + (int)y * map_width] == ' ')
		return ('4');
	write(1, "! ", 2);
	return (0);
}
*/

/*
 * Бросит луч. Вернет его длину, номер текстуры и координату столкновения
 */
static t_ray	find_ray_length(t_pl player, char *map, int map_width)
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
//	ray.wall_dir = wall_direction(map, x, y, map_width);
	ray.ntex = map[(int)x + (int)y * map_width];
	ray.length = c;
	if (ray.length < 1.0)
		ray.length = 1.0;
	return (ray);
}

t_ray	*ray_cast(t_point win, t_point map_size,
				   char *map, t_pl player)
{
	t_ray	*ray;
	int		i;
	double	t;

	if (!(ray = (t_ray *)malloc(sizeof(t_ray) * win.x)))
		print_error_and_close_app(__FILE__, __FUNCTION__, __LINE__);
	i = 0;
	while (i < win.x)
	{
		t = player.direction;
		player.direction = (player.direction - (double)(player.fov) / 2) +
						   ((double)(player.fov * i) / win.x);
		ray[i] = find_ray_length(player, map, map_size.x);
		ray[i].length = (int)((double)win.y /
				(ray[i].length * cos(t - player.direction)));
		if ((int)(ray[i].length) >= win.y)
			ray[i].length = win.y;
		player.direction = t;
		i++;
	}
	return (ray);
}