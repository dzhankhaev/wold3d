/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeulah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:00:09 by abeulah           #+#    #+#             */
/*   Updated: 2020/03/11 15:00:11 by abeulah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			check_map(int i, const char *buf)
{
	int		temp;
	int		k;

	//на нулевой строке 2 символа, 1й - цифра, 2й - конец строки
	if (i < 2 && buf[0] < '1' && buf[0] > '9' && buf[1] != '\n')
		return (0);
	temp = (int)(buf[0] - '0');
	/*
	 * карта квадратная
	 * Количество прочитанных символов должно совпадать с размерами +
	 * 2 символа на нулевой строке +
	 * нужно учитывать символ конца строки на каждой строке
	 */
	if ((temp + 1) * temp + 2 != i)
		return (0);
	k = 1;
	//в конце каждой строки должен быть \n
	while (k <= temp)
		if (buf[1 + (temp + 1) * k++] != '\n')
			return (0);
	/*
	 * 0 показывает изначальное положение
	 * 1 стенки
	 * ' ' пустоты
	 */
	k = 2;
	temp = 0;
	while (k < i)
	{
		if (!(buf[k] == '0' || buf[k] == '1' ||
		buf[k] == ' ' || buf[k] == '\n'))
			return (0);
		if (buf[k++] == '0')
			temp++;
	}
	if (temp != 1)
		return (0);
	return (1);
}

//этот маразм с циклами чтобы подогнать под норму
static int	cicle(int k, int q, const char *buf)
{
	int		temp;

	temp = get_map_size(buf).x;
	while (q < temp)
	{
		if (buf[k] != '1')
			return (1);
		q++;
		k++;
	}
	return (0);
}

static int	cicle2(int k, int q, const char *buf)
{
	int		temp;

	temp = get_map_size(buf).x;
	while (q < temp)
	{
		if (buf[k] != '1')
			return (1);
		k = 2 + (temp + 1) * q;
		q++;
	}
	return (0);
}

int			check_map_borders(const char *buf)
{
	int		temp;
	int		k;
	int		q;

	//только квадратные карты
	temp = get_map_size(buf).x;
	//первая строка
	if (cicle(2, 0, buf))
		return (0);
	//последняя строка
	if (cicle(2 + (temp + 1) * (temp - 1), 0, buf))
		return (0);
	//первый столбец
	if (cicle2(2, 1, buf))
		return (0);
	//последний столбец
	q = 1;
	k = (temp + 1) * q;
	while (q < temp)
	{
		if (buf[k] != '1')
			return (0);
		q++;
		k = (temp + 1) * q;
	}
	return (1);
}
