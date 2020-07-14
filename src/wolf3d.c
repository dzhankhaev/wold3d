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

int			fish_eye_fix(int win_height, t_ray ray)
{
	return ((int)((double)win_height / (ray.length * cos(ray.angle))) / 2);
}

int 		main()
{
	char	*map;
	t_point	map_size;
	t_mlx	w;
	t_pl	player;
	t_ray	*ray;

	map = create_map("maps/map1", &map_size);
	init_mlx(&w);
	init_player(&player, map, map_size.x);
	ray = find_ray_length(w.width, map_size, map, player);



	int j;
	int i = 0;
	char	*temp;
	char	*temp2;
	int		length;

	while (i < w.width)
	{
		temp = (char *)(w.line + (i * 4));
//		length = fish_eye_fix(w.height, ray[i]);
		length = (int)((double)w.height / ray[i].length);
		j = w.height / 2 - length / 2;
		while (j < w.height / 2 + length / 2)
		{
			temp2 = (char *)(temp + (w.width * 4 * j));
			temp2[2] = (char)255;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(w.mlx, w.win, w.img, 0, 0);
	mlx_loop(w.mlx);
	return (0);
}
