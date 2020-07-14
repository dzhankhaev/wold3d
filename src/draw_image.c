#include "wolf3d.h"

static int	fish_eye_fix(int win_height, t_ray ray)
{
	int		column_height;

//	return (int)((double)win_height / (ray.length));
	column_height = (int)((double)win_height / (ray.length * cos(ray.angle)));
	if (column_height > win_height)
		return (win_height);
	return (column_height);
}

static void	draw_floor(char *line, t_ray *ray, int win_height, int win_width)
{
	int		j;
	int		i;
	char	*temp;
	char	*temp2;
	int		length;

	i = 0;
	while (i < win_width)
	{
		temp = (char *)(line + (i * 4));
		if (ray[i].length < 1)
			ray[i].length = 1;
		length = fish_eye_fix(win_height, ray[i]);
		j = win_height / 2 + length / 2;
		while (j < win_height)
		{
			temp2 = (char *)(temp + (win_width * 4 * j));
			temp2[0] = (char)200;
			temp2[1] = (char)200;
			temp2[2] = (char)200;
			j++;
		}
		i++;
	}
}

static void	draw_sky(char *line, t_ray *ray, int win_height, int win_width)
{
	int		j;
	int		i;
	char	*temp;
	char	*temp2;
	int		length;

	i = 0;
	while (i < win_width)
	{
		temp = (char *)(line + (i * 4));
		if (ray[i].length < 1)
			ray[i].length = 1;
		length = fish_eye_fix(win_height, ray[i]);
		j = 0;
		while (j < win_height / 2 - length / 2)
		{
			temp2 = (char *)(temp + (win_width * 4 * j));
			temp2[0] = (char)255;
			temp2[1] = (char)255;
			temp2[2] = (char)255;
			j++;
		}
		i++;
	}
}

void		draw_image(t_mlx w, t_ray *ray)
{
	int		j;
	int		i;
	char	*temp;
	char	*temp2;
	int		length;

	i = 0;
	while (i < w.width)
	{
		temp = (char *)(w.line + (i * 4));
		if (ray[i].length < 1)
			ray[i].length = 1;
		length = fish_eye_fix(w.height, ray[i]);
		j = w.height / 2 - length / 2;
		while (j < w.height / 2 + length / 2)
		{
			temp2 = (char *)(temp + (w.width * 4 * j));
			temp2[0] = (char)0;
			temp2[1] = (char)0;
			temp2[2] = (char)255;
			j++;
		}
		i++;
	}
	draw_sky(w.line, ray, w.height, w.width);
	draw_floor(w.line, ray, w.height, w.width);
	mlx_put_image_to_window(w.mlx, w.win, w.img, 0, 0);
}