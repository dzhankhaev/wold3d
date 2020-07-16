/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeulah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:00:09 by abeulah           #+#    #+#             */
/*   Updated: 2020/03/11 15:00:11 by abeulah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
 * Выделит память и скопирует из str n символов, в конце поставит 0
 * Вернет выделенную память. Вернет 0 в случае ошибки выделения памяти.
 * От выхода за границы не защищена
 */
static char	*copy_n_chars(const char *str, int n)
{
	char	*a;
	int		i;

	a = (char *)malloc(sizeof(char) * (n + 1));
	if (!a)
		return (0);
	i = 0;
	while (i < n)
	{
		a[i] = str[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}

/*
 * Прочтет файл. Проверит его на ошибки.
 * Работает только на квадратные карты с одноразрядным размером
 * Выделит память и вернет строку с прочитанным файлом.
 */
static char	*read_file(char *file_name)
{
	int		fd;
	int		i;
	char	buf[BUF_SIZE];
	char	*map;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		print_error_and_close_app(__FILE__, __FUNCTION__, __LINE__);
	if ((i = (int)read(fd, buf, BUF_SIZE)) == -1)
		print_error_and_close_app(__FILE__, __FUNCTION__, __LINE__);
	close(fd);
	if (!check_map(i, buf))
		print_error_and_close_app(__FILE__, __FUNCTION__, __LINE__);
	if (!check_map_borders(buf))
		print_error_and_close_app(__FILE__, __FUNCTION__, __LINE__);
	if (!(map = copy_n_chars(buf, i)))
		print_error_and_close_app(__FILE__, __FUNCTION__, __LINE__);
	return (map);
}

char		*create_map(char *file_name, t_point *map_size)
{
	int		i;
	int		j;
	int		k;
	char	*map;
	char	*map_with_sizes;

	map_with_sizes = read_file(file_name);
	*map_size = get_map_size(map_with_sizes);
	if (!(map = (char *)malloc(sizeof(char) *
			(map_size->x * map_size->y + 1))))
		print_error_and_close_app(__FILE__, __FUNCTION__, __LINE__);
	map[map_size->x * map_size->y] = '\0';
	i = 0;
	k = 0;
	while (i < map_size->y)
	{
		j = 0;
		while (j < map_size->x)
			map[k++] = map_with_sizes[2 + j++ + i * (map_size->x + 1)];
		i++;
	}
	free(map_with_sizes);
	return (map);
}
