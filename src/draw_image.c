#include "wolf3d.h"

static int	fish_eye_fix(int win_height, t_ray ray)
{
	int		column_height;

	column_height = (int)((double)win_height / (ray.length * cos(ray.angle)));
	if (column_height > win_height)
		return (win_height);
	return (column_height);
}

static void	draw_floor(char *temp, t_ray ray, int win_height, int win_width)
{
	int		j;
	char	*temp2;

	j = win_height / 2 + (int)ray.length / 2;
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
	while (j < win_height / 2 - (int)ray.length / 2)
	{
		temp2 = (char *)(temp + (win_width * 4 * j));
		temp2[0] = (char)200;
		temp2[1] = (char)140;
		temp2[2] = (char)140;
		j++;
	}
}

static void	draw_walls(char *temp, t_ray ray, int win_height, int win_width)
{
	int		j;
	char	*temp2;

	j = win_height / 2 - (int)ray.length / 2;
	while (j < win_height / 2 + (int)ray.length / 2)
	{
		temp2 = (char *)(temp + (win_width * 4 * j));
		temp2[0] = (char)100;
		temp2[1] = (char)140;
		temp2[2] = (char)140;
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
		if (ray[i].length < 1)
			ray[i].length = 1;
		ray[i].length = (double)fish_eye_fix(w.height, ray[i]);
		draw_sky(temp, ray[i], w.height, w.width);
		draw_walls(temp, ray[i], w.height, w.width);
		draw_floor(temp, ray[i], w.height, w.width);
		i++;
	}
	mlx_put_image_to_window(w.mlx, w.win, w.img, 0, 0);
}