/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeulah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:00:09 by abeulah           #+#    #+#             */
/*   Updated: 2020/03/11 15:00:11 by abeulah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static char	*integer_to_string(int n)
{
	int		i;
	int		c;
	char	*arr;

	i = 0;
	c = n;
	while (c > 0)
	{
		c /= 10;
		i++;
	}
	if (!(arr = (char *)malloc(sizeof(char) * (i + 1))))
	{
		write(1, "Error in integer_to_string function in utilits.c\n",
	49);
		exit(0);
	}
	arr[i--] = '\0';
	while (n > 0)
	{
		arr[i--] = (n % 10) + '0';
		n /= 10;
	}
	return (arr);
}

void		print_error_and_close_app(const char *file, const char *function,
		int line)
{
	int		i;
	char	*l;

	l = integer_to_string(line);
	i = 0;
	write(1, "ERROR: In file ", 15);
	while (file[i] != '\0')
		write(1, &file[i++], 1);
	write(1, " on line ", 9);
	i = 0;
	while (l[i] != '\0')
		write(1, &l[i++], 1);
	write(1, ", function ", 11);
	i = 0;
	while (function[i] != '\0')
		write(1, &function[i++], 1);
	write(1, " is not success finishing!\n", 27);
	exit(0);
}

t_point		get_map_size(const char *map)
{
	t_point	a;

	a.x = map[0] - '0';
	a.y = map[0] - '0';
	return (a);
}

t_point		get_win_size(t_mlx w)
{
	t_point	a;

	a.x = w.width;
	a.y = w.height;
	return (a);
}
