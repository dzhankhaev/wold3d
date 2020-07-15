#ifndef WOLF3D_H
# define WOLF3D_H

# define CL_USE_DEPRECATED_OPENCL_1_2_APIS
# define BUF_SIZE 100
# define WIDTH 1280
# define HEIGHT 720
# define BPP 4
# define ENDIAN 0
# define FOV 60
# define PLAYER_DIR 0
# define RAY_STEP 0.01
# define PLAYER_STEP 0.1
# define PLAYER_ROTATE 5

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

typedef struct	s_ray
{
	double		x;
	double		y;
	double		length;
	double		angle;
}				t_ray;

typedef struct	s_pl
{
	double		x;
	double		y;
	double		direction;
	double		fov;
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
	t_mlx		*w;
	t_pl		*player;
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
 * key_hooks.c
 */
int				key_hooks(int key, void *temp);

/*
 * draw_image.c
 * Отрисует изображение в соответствии с текущей позицией и взглядом
 */
void			draw_image(t_mlx w, t_ray *ray);

/*
 * ray_cast.c
 * Выделит память и вернёт массив лучей с координатами столкновений
 * и длинами лучей
 */
t_ray			*find_ray_length(int width, t_point map_size,
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

void			angle_more_than_45_2(t_line p, t_mlx *w);
void			angle_less_than_45_2(t_line p, t_mlx *w);
void			angle_more_than_45_1(t_line p, t_mlx *w);
void			angle_less_than_45_1(t_line p, t_mlx *w);
void			render_a_line(t_line p, t_mlx *w);

#endif
