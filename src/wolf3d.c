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

static void	init_player(t_pl *player, char *map, int map_width)
{
	int		i;

	i = 0;
	while (map[i] != '2')
		i++;
	player->x = (double)(i % map_width) + 0.5;
	player->y = i / map_width + 0.5;
	player->direction = (PLAYER_DIR * M_PI) / 180;
	player->fov = (FOV * M_PI) / 180;
}

int 		main()
{
	char	*map;
	t_point	map_size;
	t_mlx	w;
	t_pl	player;
	t_all	all;


	map = create_map("maps/map1", &map_size);
	init_mlx(&w);
	init_player(&player, map, map_size.x);
	t_ray *ray = find_ray_length(w.width, map_size, map, player);
	draw_image(w, ray);
	free(ray);
	all.w = &w;
	all.player = &player;
	all.map = map;
	all.map_size = map_size;
	mlx_key_hook(w.win, key_hooks, (void *)&all);
	mlx_loop(w.mlx);
	return (0);
}
