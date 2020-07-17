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
	return ('0');
}

double rad(double a)
{
	return ((a * M_PI) / 180);
}

/*
 * Бросит луч. Вернет номер текстуры и направление стены
 * В указателе length будет записана длина луча
 */
static t_wall	find_ray_length(double *length, t_pl player, char *map,
		int map_width)
{
	t_wall	wall;
	double	x;
	double	y;
	double 	x2;
	double 	y2;

	*length = 0;

	if (player.direction == 0)
		player.direction += rad(0.1);
	if (player.direction == rad(90))
		player.direction += rad(0.1);
	if (player.direction == rad(180))
		player.direction += rad(0.1);
	if (player.direction == rad(270))
		player.direction += rad(0.1);
	x = 0;
	y = 0;
	x2 = 0;
	y2 = 0;
	int i = 1;
	int k = 0;
	while (map[(int)(x + player.x) + (int)(y + player.y - k) * map_width] != '1')
	{
		if (player.direction > rad(180) || player.direction < 0)
		{
			y = -1 * (player.y - ((int)(player.y + 1) - i));
			k = 1;
		}
		else
		{
			y = (int)(player.y) + i - player.y;
			k = 0;
		}
		x = y / tan(player.direction);
		if ((int)(x + player.x) >= map_width || (int)(x + player.x) <= 0)
			break ;
		i++;
	}
	i = 1;
	k = 0;
	while (map[(int)(x2 + player.x - k) + (int)(y2 + player.y) * map_width] != '1')
	{
		if (player.direction > rad(90) && player.direction < rad(270))
		{
			x2 = -1 * (player.x - ((int)(player.x + 1) - i));
			k = 1;
		}
		else
		{
			x2 = (int)(player.x) + i - player.x;
			k = 0;
		}
		y2 = x2 * tan(player.direction);
		if ((int)(y2 + player.y) >= map_width || (int)(y2 + player.y) <= 0)
			break ;
		i++;
	}
	if (sqrt(y * y + x * x) < sqrt(x2 * x2 + y2 * y2))
		*length = sqrt(y * y + x * x);
	else
		*length = sqrt(x2 * x2 + y2 * y2);
	wall.dir = '8';
	return (wall);
}

t_wall			*ray_cast(t_point win, t_point map_size,
	char *map, t_pl player)
{
	t_wall		*wall;
	int			i;
	double		t;
	double		length;

	if (!(wall = (t_wall *)malloc(sizeof(t_wall) * win.x)))
		print_error_and_close_app(__FILE__, __FUNCTION__, __LINE__);
	i = 0;
	while (i < win.x)
	{
		t = player.direction;
		player.direction = (player.direction - (double)(player.fov) / 2) +
	((double)(player.fov * i) / win.x);
		if (player.direction < 0)
			player.direction = rad(360) + player.direction;
		if (player.direction > rad(360))
			player.direction -= rad(360);
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
