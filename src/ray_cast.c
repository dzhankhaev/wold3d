/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeulah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:00:09 by abeulah           #+#    #+#             */
/*   Updated: 2020/03/11 15:00:11 by abeulah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static double	y_walk(t_pl player, int map_width, char *map, char *wall_dir)
{
	double	x;
	double	y;
	int		i;

	x = 0;
	y = 0;
	i = 1;
	while (map[(int)(x + player.x) + (int)(y + player.y) * map_width] != '1')
	{
		//опять виновата норма
		//при выполнении этого условия в условии цикла от y надо отнять 1, но места для строк нет
		//- 0.000000001 вообще не нужно
		if (player.direction > RAD180 || player.direction < 0)
		{
			y = -1 * (player.y - ((int)(player.y + 1) - i)) - 0.000000001;
			*wall_dir = '1';
		}
		else
		{
			y = (int)(player.y) + i - player.y;
			*wall_dir = '3';
		}
		x = y / tan(player.direction);
		if ((int)(x + player.x) >= map_width || (int)(x + player.x) <= 0)
			break ;
		i++;
	}
	return (sqrt(y * y + x * x));
}

static double	x_walk(t_pl player, int map_width, char *map, char *wall_dir)
{
	double	x;
	double	y;
	int		i;

	x = 0;
	y = 0;
	i = 1;
	while (map[(int)(x + player.x) + (int)(y + player.y) * map_width] != '1')
	{
		if (player.direction > RAD90 && player.direction < RAD270)
		{
			x = -1 * (player.x - ((int)(player.x + 1) - i)) - 0.000000001;
			*wall_dir = '4';
		}
		else
		{
			x = (int)(player.x) + i - player.x;
			*wall_dir = '2';
		}
		y = x * tan(player.direction);
		if ((int)(y + player.y) >= map_width || (int)(y + player.y) <= 0)
			break ;
		i++;
	}
	return (sqrt(y * y + x * x));
}

/*
 * Бросит луч. Вернет номер текстуры и направление стены
 * В указателе length будет записана длина луча
 * 1 - север, 2 - восток, 3 - юг, 4 - запад
 */
static t_wall	find_ray_length(double *length, t_pl player, char *map,
		int map_width)
{
	t_wall	wall;
	double 	tempx;
	double 	tempy;
	char	wall_dir1;
	char	wall_dir2;

	*length = 0;
	if (player.direction == RAD90)
		player.direction += RAD0_1;
	if (player.direction == RAD270)
		player.direction += RAD0_1;
	tempx = x_walk(player, map_width, map, &wall_dir1);
	tempy = y_walk(player, map_width, map, &wall_dir2);
	if (tempx < tempy)
	{
		*length = tempx;
		wall.dir = wall_dir1;
	}
	else
	{
		*length = tempy;
		wall.dir = wall_dir2;
	}
	return (wall);
}

t_wall			*ray_cast(t_point win, t_point map_size,
	char *map, t_pl player)
{
	t_wall		*wall;
	int			i;
	double		t;
	double		length;
//ради 25 строк i инициализируется так
	if ((i = 0) || !(wall = (t_wall *)malloc(sizeof(t_wall) * win.x)))
		print_error_and_close_app(__FILE__, __FUNCTION__, __LINE__);
	while (i < win.x)
	{
		t = player.direction;
		player.direction = (player.direction - (double)(player.fov) / 2) +
	((double)(player.fov * i) / win.x);
		if (player.direction < 0)
			player.direction = RAD360 + player.direction;
		if (player.direction > RAD360)
			player.direction -= RAD360;
		wall[i] = find_ray_length(&length, player, map, map_size.x);
		wall[i].length = (int)((double)win.y /
	(length * cos(t - player.direction)));
		if (wall[i].length >= win.y)
			wall[i].length = win.y;
		player.direction = t;
		i++;
	}
	return (wall);
}
