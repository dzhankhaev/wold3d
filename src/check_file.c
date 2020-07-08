#include "wolf3d.h"

int	check_map(int i, const char *buf)
{
	int		temp, k;

	//на нулевой строке 2 символа, 1й - цифра, 2й - конец строки
	if (i < 2 && buf[0] < '1' && buf[0] > '9' && buf[1] != '\n')
		return (0);
	temp = buf[0] - '0';
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
	{
		if (buf[1 + (temp + 1) * k] != '\n')
			return (0);
		k++;
	}
	/*
	 * 2 показывает изначальное положение
	 * 1 стенки
	 * 0 пустоты
	 */
	k = 2;
	temp = 0;
	while (k < i)
	{
		if (!(buf[k] == '0' || buf[k] == '1' || buf[k] == '2'
		|| buf[k] == '\n'))
			return (0);
		if (buf[k] == '2')
			temp++;
		k++;
	}
	if (temp != 1)
		return (0);
	return (1);
}

/*
 * Прочтет указанный файл и проверит его на ошибки
 * Вернет прочитанный файл
 * Выделяет память, нужно чистить
 * ЧИТАЕТ ТОЛЬКО КВАДРАТНЫЕ КАРТЫ
 */
int	check_map_borders(int i, const char *buf)
{
	int		temp, k, q;

	//только квадратные карты
	temp = get_map_size(buf).x;
	//первая строка
	k = 2;
	q = 0;
	while (q < temp)
	{
		if (buf[k] != '1')
			return (0);
		q++;
		k++;
	}
	//последняя строка
	k = 2 + (temp + 1) * (temp - 1);
	q = 0;
	while (q < temp)
	{
		if (buf[k] != '1')
			return (0);
		q++;
		k++;
	}
	//первый столбец
	k = 2;
	q = 1;
	while (q < temp)
	{
		if (buf[k] != '1')
			return (0);
		k = 2 + (temp + 1) * q;
		q++;
	}
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
