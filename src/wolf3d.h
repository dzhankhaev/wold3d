/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeulah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:00:09 by abeulah           #+#    #+#             */
/*   Updated: 2020/03/11 15:00:11 by abeulah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define BUF_SIZE 100
# define WIDTH 1280
# define HEIGHT 720
# define BPP 4
# define ENDIAN 0
# define FOV 60
# define PLAYER_DIR 0
# define PLAYER_STEP 0.05
# define PLAYER_ROTATE 1.5
# define TRUE 1
# define FALSE 0
# define RAD90 1.570796
# define RAD180 3.141593
# define RAD270 4.712389
# define RAD360 6.283185
# define RAD0_1 0.001745

# include <stdio.h>
# include <CL/cl.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "../minilibx/mlx.h"
typedef struct	s_line
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
}				t_line;

typedef struct	s_deltas
{
	int			dx;
	int			dy;
	int			error;
	int			derror;

}				t_deltas;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_wall
{
	int			length;
	char		dir;
}				t_wall;

typedef struct	s_pl
{
	double		x;
	double		y;
	double		direction;
	double		fov;
	int			right;
	int			left;
	int			up;
	int			down;
}				t_pl;

typedef struct	s_mlx
{
	int			width;
	int			height;
	int			bpp;
	int			size;
	int			endian;
	void		*mlx;
	void		*win;
	void		*img;
	char		*line;
}				t_mlx;

typedef struct	s_all
{
	t_mlx		w;
	t_pl		player;
	char		*map;
	t_point		map_size;

}				t_all;

/*
 * move.c
 * Сменит направление относительно текущего на указанный угол в градусах
 * Все поля структуры используются и должны быть заполнены
 */
void			player_rot(t_all *all, double rotate);
/*
 * move.c
 * Сделает шаг. Вперёд - положительное число, назад - отрицательное
 * Все поля структуры используются и должны быть заполнены
 */
void			player_step(t_all *all, double step);

/*
 * hooks.c
 */
int				key_press(int key, void *player);
int				key_release(int key, void *player);
int				loop_hooks(void *temp);
/*
 * draw_image.c
 * Отрисует изображение в соответствии с текущей позицией и взглядом
 */
void			draw_image(t_mlx w, t_wall *wall);

/*
 * ray_cast.c
 * Выделит память и вернет массив с уже просчитаными длинами стен
 * остаётся только отрисовать
 */
t_wall			*ray_cast(t_point win, t_point map_size,
	char *map, t_pl player);

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
t_point			get_win_size(t_mlx w);

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
int				check_map_borders(const char *buf);

/*
 * Тестовые. Распечатает карту.
 */
void			print_map(char *map, t_point map_size);

#endif
