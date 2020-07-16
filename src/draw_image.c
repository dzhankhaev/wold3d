/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeulah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:00:09 by abeulah           #+#    #+#             */
/*   Updated: 2020/03/11 15:00:11 by abeulah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	draw_floor(char *temp, t_wall wall, int win_height, int win_width)
{
	int		j;
	char	*temp2;

	j = win_height / 2 + wall.length / 2;
	while (j < win_height)
	{
		temp2 = (char *)(temp + (win_width * 4 * j));
		temp2[0] = (char)64;
		temp2[1] = (char)84;
		temp2[2] = (char)92;
		j++;
	}
}

static void	draw_sky(char *temp, t_wall wall, int win_height, int win_width)
{
	int		j;
	char	*temp2;

	j = 0;
	while (j < win_height / 2 - wall.length / 2)
	{
		temp2 = (char *)(temp + (win_width * 4 * j));
		temp2[0] = (char)(220 - j / 2);
		temp2[1] = (char)(180 - j / 2);
		temp2[2] = (char)(150 - j / 3);
		j++;
	}
}

static void	draw_walls(char *temp, t_wall wall, int win_height, int win_width)
{
	int		j;
	char	*temp2;

	j = win_height / 2 - wall.length / 2;
	while (j < win_height / 2 + wall.length / 2)
	{
		temp2 = (char *)(temp + (win_width * 4 * j));
		temp2[0] = (char)(27 * (wall.dir + '0'));
		temp2[1] = (char)(27 * (wall.dir + '0'));
		temp2[2] = (char)(27 * (wall.dir + '0'));
		j++;
	}
}

void		draw_image(t_mlx w, t_wall *wall)
{
	int			i;
	char		*temp;

	i = 0;
	while (i < w.width)
	{
		temp = (char *)(w.line + (i * 4));
		draw_sky(temp, wall[i], w.height, w.width);
		draw_walls(temp, wall[i], w.height, w.width);
		draw_floor(temp, wall[i], w.height, w.width);
		i++;
	}
	mlx_put_image_to_window(w.mlx, w.win, w.img, 0, 0);
}
