/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeulah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:00:09 by abeulah           #+#    #+#             */
/*   Updated: 2020/03/11 15:00:11 by abeulah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		player_rot(t_all *all, double rotate)
{
	t_mlx	w;
	t_pl	*player;
	t_wall	*wall;
	char	*map;
	t_point	map_size;

	w = all->w;
	player = &(all->player);
	map = all->map;
	map_size = all->map_size;
	if (player->direction >= RAD360)
		player->direction = (rotate * M_PI) / 180;
	else if (player->direction <= 0)
		player->direction = ((360 + rotate) * M_PI) / 180;
	else
		player->direction += (rotate * M_PI) / 180;
	wall = ray_cast(get_win_size(w), map_size, map, *player);
	draw_image(w, wall);
	free(wall);
}

static int	check_collision(const char *map, int map_width, double x, double y)
{
	if (map[(int)x + (int)y * map_width] != '1')
		return (1);
	return (0);
}

void		player_step(t_all *all, double step)
{
	t_mlx	w;
	t_pl	*player;
	t_wall	*wall;
	char	*map;
	t_point	map_size;

	w = all->w;
	player = &(all->player);
	map = all->map;
	map_size = all->map_size;
	if (check_collision(map, map_size.x,
			player->x + (step + step / 100) * cos(player->direction),
			player->y + (step + step / 100) * sin(player->direction)))
	{
		player->x += step * cos(player->direction);
		player->y += step * sin(player->direction);
		wall = ray_cast(get_win_size(w), map_size, map, *player);
		draw_image(w, wall);
		free(wall);
		return ;
	}
}
