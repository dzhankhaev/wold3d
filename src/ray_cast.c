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
	return (0);
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

	*length = 0;
	x = player.x;
	y = player.y;
	while (map[(int)x + (int)y * map_width] != '1')
	{
		x = player.x + *length * cos(player.direction);
		y = player.y + *length * sin(player.direction);
		*length += RAY_STEP;
	}
	wall.dir = wall_direction(map, x, y, map_width);
	return (wall);
}

t_wall			*ray_cast(t_point win, t_point map_size,
	char *map, t_pl player)
{
	t_wall	*wall;
	int		i;
	double	t;
	double	length;

	if (!(wall = (t_wall *)malloc(sizeof(t_wall) * win.x)))
		print_error_and_close_app(__FILE__, __FUNCTION__, __LINE__);
	i = 0;
	while (i < win.x)
	{
		t = player.direction;
		player.direction = (player.direction - (double)(player.fov) / 2) +
	((double)(player.fov * i) / win.x);
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
