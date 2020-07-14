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
	t_ray	*ray;

	map = create_map("maps/map1", &map_size);
	init_mlx(&w);
	init_player(&player, map, map_size.x);
	ray = find_ray_length(w.width, map_size, map, player);


/*
	int j = 0;
	int i = 0;
	char	*temp;
	int		length;

	while (i < w.width)
	{
		temp = (char *)(w.line + (i * 4));
		j = 0;
		length = w.height - (int)(ray[i].length) * 30;
		while (j < w.height)
		{
			if (j < length)
			{
				temp[2] = (char)255;
			}
			else
			{
				temp[0] = (char)255;
				temp[1] = (char)255;
				temp[2] = (char)255;
			}
			j++;
			temp = (char *)(temp + (w.width * 4));
		}
		i++;
	}
	i = 0;
	while (i < w.width)
	{
		temp = (char *)(w.line + (i * 4));
		j = 0;
		length = (int)(ray[i].length) * 30;
		while (j < w.height)
		{
			if (j > length)
			{
				temp[2] = (char)255;
			}
			else
			{
				temp[0] = (char)255;
				temp[1] = (char)255;
				temp[2] = (char)255;
			}
			j++;
			temp = (char *)(temp + (w.width * 4));
		}
		i++;
	}
*/
	mlx_put_image_to_window(w.mlx, w.win, w.img, 0, 0);
	mlx_loop(w.mlx);
	return (0);
}
