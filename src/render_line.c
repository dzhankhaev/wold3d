#include "wolf3d.h"

void	angle_less_than_45_1(t_line p, t_mlx *w)
{
	char		*temp;
	t_deltas	d;

	d.dx = abs(p.x1 - p.x0);
	d.dy = abs(p.y1 - p.y0);
	d.error = 0;
	d.derror = d.dy + 1;
	while (p.x0 < p.x1)
	{
		temp = (char *)(w->line + (p.y0 * 4 * w->width));
		temp[p.x0 * 4] = (char)255;
		temp[p.x0 * 4 + 1] = (char)255;
		temp[p.x0 * 4 + 2] = (char)255;
		d.error += d.derror;
		if (d.error >= d.dx + 1)
		{
			p.y0++;
			d.error -= d.dx + 1;
		}
		p.x0++;
	}
}

void	angle_more_than_45_1(t_line p, t_mlx *w)
{
	char		*temp;
	t_deltas	d;

	d.dx = abs(p.x1 - p.x0);
	d.dy = abs(p.y1 - p.y0);
	d.error = 0;
	d.derror = d.dx + 1;
	while (p.y0 < p.y1)
	{
		temp = (char *)(w->line + (p.y0 * 4 * w->width));
		temp[p.x0 * 4] = (char)255;
		temp[p.x0 * 4 + 1] = (char)255;
		temp[p.x0 * 4 + 2] = (char)255;
		d.error += d.derror;
		if (d.error >= d.dy + 1)
		{
			p.x0++;
			d.error -= d.dy + 1;
		}
		p.y0++;
	}
}

void	angle_less_than_45_2(t_line p, t_mlx *w)
{
	char		*temp;
	t_deltas	d;

	d.dx = abs(p.x1 - p.x0);
	d.dy = abs(p.y1 - p.y0);
	d.error = 0;
	d.derror = d.dy + 1;
	while (p.x0 > p.x1)
	{
		temp = (char *)(w->line + (p.y0 * 4 * w->width));
		temp[p.x0 * 4] = (char)255;
		temp[p.x0 * 4 + 1] = (char)255;
		temp[p.x0 * 4 + 2] = (char)255;
		d.error += d.derror;
		if (d.error >= d.dx + 1)
		{
			p.y0++;
			d.error -= d.dx + 1;
		}
		p.x0--;
	}
}

void	angle_more_than_45_2(t_line p, t_mlx *w)
{
	char		*temp;
	t_deltas	d;

	d.dx = abs(p.x1 - p.x0);
	d.dy = abs(p.y1 - p.y0);
	d.error = 0;
	d.derror = d.dx + 1;
	while (p.y0 > p.y1)
	{
		temp = (char *)(w->line + (p.y0 * 4 * w->width));
		temp[p.x0 * 4] = (char)255;
		temp[p.x0 * 4 + 1] = (char)255;
		temp[p.x0 * 4 + 2] = (char)255;
		d.error += d.derror;
		if (d.error >= d.dy + 1)
		{
			p.x0++;
			d.error -= d.dy + 1;
		}
		p.y0--;
	}
}