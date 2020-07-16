/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeulah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:00:09 by abeulah           #+#    #+#             */
/*   Updated: 2020/03/11 15:00:11 by abeulah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		init_mlx(t_mlx *w)
{
	w->width = WIDTH;
	w->height = HEIGHT;
	if (!(w->mlx = mlx_init()))
		print_error_and_close_app(__FILE__, __FUNCTION__, __LINE__);
	if (!(w->win = mlx_new_window(w->mlx, w->width, w->height, "wolf3d")))
		print_error_and_close_app(__FILE__, __FUNCTION__, __LINE__);
	if (!(w->img = mlx_new_image(w->mlx, w->width, w->height)))
		print_error_and_close_app(__FILE__, __FUNCTION__, __LINE__);
	w->bpp = BPP;
	w->size = w->bpp * w->width;
	w->endian = ENDIAN;
	w->line = mlx_get_data_addr(w->img, &w->bpp, &w->size, &w->endian);
}

/*
 * запишет позицию игрока и сотрет её из карты, заменив пустотой
 */
static void		init_player(t_pl *player, char *map, int map_width)
{
	int		i;

	i = 0;
	while (map[i] != '0')
		i++;
	player->x = (double)(i % map_width) + 0.5;
	player->y = i / map_width + 0.5;
	map[i] = ' ';
	player->direction = (PLAYER_DIR * M_PI) / 180;
	player->fov = (FOV * M_PI) / 180;
	player->right = FALSE;
	player->left = FALSE;
	player->up = FALSE;
	player->down = FALSE;
}

int				main(void)
{
	t_wall	*wall;
	t_all	all;

	all.map = create_map("maps/map1", &(all.map_size));
	init_mlx(&(all.w));
	init_player(&(all.player), all.map, all.map_size.x);
	wall = ray_cast(get_win_size(all.w), all.map_size, all.map, all.player);
	draw_image(all.w, wall);
	free(wall);
	mlx_hook(all.w.win, 2, 1L << 0, key_press,
			(void *)&(all.player));
	mlx_hook(all.w.win, 3, 1L << 1, key_release,
			(void *)&(all.player));
	mlx_loop_hook(all.w.mlx, loop_hooks, (void *)&all);
	mlx_loop(all.w.mlx);
	return (0);
}
