
#include "wolf3d.h"

static t_line	swap_coords(t_line p)
{
	int t;

	t = p.x0;
	p.x0 = p.x1;
	p.x1 = t;
	t = p.y0;
	p.y0 = p.y1;
	p.y1 = t;
	return (p);
}

static void		from_left_top_to_right_down(t_line p, t_mlx *w)
{
	if (abs(p.x1 - p.x0) > abs(p.y1 - p.y0))
		angle_less_than_45_1(p, w);
	else
		angle_more_than_45_1(p, w);
}

static void		from_right_top_to_left_down(t_line p, t_mlx *w)
{
	if (abs(p.x1 - p.x0) > abs(p.y1 - p.y0))
		angle_less_than_45_2(p, w);
	else
		angle_more_than_45_2(swap_coords(p), w);
}

static void		render_a_perpendicular_line(t_line p, t_mlx *w)
{
	char	*temp;

	if (p.x0 == p.x1)
	{
		p = p.y0 > p.y1 ? swap_coords(p) : p;
		while (p.y0 < p.y1)
		{
			temp = (char *)(w->line + (p.y0++ * 4 * w->width));
			temp[p.x0 * 4] = (char)255;
			temp[p.x0 * 4 + 1] = (char)255;
			temp[p.x0 * 4 + 2] = (char)255;
		}
	}
	else
	{
		p = p.x0 > p.x1 ? swap_coords(p) : p;
		temp = (char *)(w->line + (p.y0 * 4 * w->width));
		while (p.x0 < p.x1)
		{
			temp[p.x0 * 4] = (char)255;
			temp[p.x0 * 4 + 1] = (char)255;
			temp[p.x0 * 4 + 2] = (char)255;
			p.x0++;
		}
	}
}

void			render_a_line(t_line p, t_mlx *w)
{
	if (p.x0 == p.x1 || p.y0 == p.y1)
		render_a_perpendicular_line(p, w);
	else if (p.x0 < p.x1 && p.y0 < p.y1)
		from_left_top_to_right_down(p, w);
	else if (p.x0 > p.x1 && p.y0 > p.y1)
		from_left_top_to_right_down(swap_coords(p), w);
	else if (p.x0 > p.x1 && p.y0 < p.y1)
		from_right_top_to_left_down(p, w);
	else if (p.x0 < p.x1 && p.y0 > p.y1)
		from_right_top_to_left_down(swap_coords(p), w);
}