#include "wolf3d.h"

static void	init_mlx(t_mlx *w)
{
	w->width = WIDTH;
	w->height = HEIGHT;
	if (!(w->mlx = mlx_init()))
		print_error_and_close_app(__FILE__, __FUNCTION__, __LINE__);
	if (!(w->win = mlx_new_window(w->mlx, w->width, w->height, "wolf3d")))
		print_error_and_close_app(__FILE__, __FUNCTION__, __LINE__);;
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
static void	init_player(t_pl *player, char *map, int map_width)
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

int 		main()
{
	char	*map;
	t_point	map_size;
	t_point	win;
	t_mlx	w;
	t_pl	player;
	t_all	all;
	t_ray	*ray;


	map = create_map("maps/map1", &map_size);
	init_mlx(&w);
	init_player(&player, map, map_size.x);
	win.x = w.width;
	win.y = w.height;
	ray = ray_cast(win, map_size, map, player);
	draw_image(w, ray);
	free(ray);
	all.w = &w;
	all.player = &player;
	all.map = map;
	all.map_size = map_size;
	mlx_hook(w.win, 2, 1L << 0, key_press, (void *)&player);
	mlx_hook(w.win, 3, 1L << 1, key_release, (void *)&player);
	mlx_loop_hook(w.mlx, loop_hooks,(void *)&all);
	mlx_loop(w.mlx);
	return (0);
}
