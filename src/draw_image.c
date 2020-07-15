#include "wolf3d.h"

static void	draw_floor(char *temp, t_ray ray, int win_height, int win_width)
{
	int		j;
	char	*temp2;

	j = win_height / 2 + ray.length / 2;
	while (j < win_height)
	{
		temp2 = (char *)(temp + (win_width * 4 * j));
		temp2[0] = (char)170;
		temp2[1] = (char)170;
		temp2[2] = (char)170;
		j++;
	}
}

static void	draw_sky(char *temp, t_ray ray, int win_height, int win_width)
{
	int		j;
	char	*temp2;

	j = 0;
	while (j < win_height / 2 - ray.length / 2)
	{
		temp2 = (char *)(temp + (win_width * 4 * j));
		temp2[0] = (char)(220 - j / 2);
		temp2[1] = (char)(180 - j / 2);
		temp2[2] = (char)(150 - j / 3);
		j++;
	}
}

static void	draw_walls(char *temp, t_ray ray, int win_height, int win_width)
{
	int		j;
	char	*temp2;

	j = win_height / 2 - ray.length / 2;
	while (j < win_height / 2 + ray.length / 2)
	{
		temp2 = (char *)(temp + (win_width * 4 * j));
		temp2[0] = (char)(27 * (ray.ntex + '0'));
		temp2[1] = (char)(27 * (ray.ntex + '0'));
		temp2[2] = (char)(27 * (ray.ntex + '0'));
		j++;
	}
}

void		draw_image(t_mlx w, t_ray *ray)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < w.width)
	{
		temp = (char *)(w.line + (i * 4));
		draw_sky(temp, ray[i], w.height, w.width);
		draw_walls(temp, ray[i], w.height, w.width);
		draw_floor(temp, ray[i], w.height, w.width);
		i++;
	}
	mlx_put_image_to_window(w.mlx, w.win, w.img, 0, 0);
}