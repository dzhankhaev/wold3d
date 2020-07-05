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
 * Проверяет корректность карты.
 * Возвращает 0 в случае ошибки и 1 в случае успеха
 */
static int	check_map(int i, const char *buf)
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
 * Проверяет корректность границ
 * Карта должна быть полностью ограничена границами
 * Возвращает 0 в случае ошибки и 1 в случае успеха
 */
static int	check_map_borders(int i, const char *buf)
{
	int		temp, k, q;

	temp = buf[0] - '0';
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

char		*read_file(char *file_name)
{
	int		fd, i;
	char	buf[100], *map;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		print_error_and_close_app(__FILE__, __FUNCTION__, __LINE__);
	if ((i = (int)read(fd, buf, 100)) == -1)
		print_error_and_close_app(__FILE__, __FUNCTION__, __LINE__);
	if (!check_map(i, buf))
		print_error_and_close_app(__FILE__, __FUNCTION__, __LINE__);
	if (!check_map_borders(i, buf))
		print_error_and_close_app(__FILE__, __FUNCTION__, __LINE__);
	if (!(map = copy_n_chars(buf, i)))
		print_error_and_close_app(__FILE__, __FUNCTION__, __LINE__);
	return (map);
}
