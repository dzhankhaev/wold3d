#ifndef WOLF3D_H
# define WOLF3D_H

# define CL_USE_DEPRECATED_OPENCL_1_2_APIS
# define BUF_SIZE 100

# include <stdio.h>
# include <CL/cl.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "../minilibx/mlx.h"

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_player
{
	t_point		position;

}				t_player;

/*
 * utilits.c
 * Напечает сообщение об ошибке и закроет программу
 * В аргументах нужно ввести __FILE__, __FUNCTION__, __LINE__
 */
void			print_error_and_close_app(const char *file,
		const char *function, int line);
/*
 * utilits.c
 * Вернет размер карты, записанный в файле. Ошибки не обрабатывает.
 * Работает только на квадратные карты с одноразрядным размером
 * Возвращает ширину x и высоту y
 */
t_point			get_map_size(const char *map);


/*
 * create_map.c
 * Вернет карту. Во вторую переменную будет записан размер карты
 * Выделяет память под карту
 */
char			*create_map(char *file_name, t_point *map_size);


/*
 * check_file.c
 * Проверяет корректность карты.
 * Возвращает 0 в случае ошибки и 1 в случае успеха
 */
int				check_map(int i, const char *buf);
/*
 * check_file.c
 * Проверяет корректность границ
 * Карта должна быть полностью ограничена границами
 * Возвращает 0 в случае ошибки и 1 в случае успеха
 */
int				check_map_borders(int i, const char *buf);

/*
 * Тестовые. Распечатает карту.
 */
void	print_map(char *map, t_point map_size);
#endif
