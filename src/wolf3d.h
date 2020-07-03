#ifndef WOLF3D_H
# define WOLF3D_H

# define CL_USE_DEPRECATED_OPENCL_1_2_APIS

# include <stdio.h>
# include <CL/cl.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "../minilibx/mlx.h"

/*
 * Прочтет указанный файл и проверит его на ошибки
 */
char	*read_file(char *file_name);
/*
 * Напечает сообщение об ошибке и закроет программу
 * В аргументах нужно ввести __FILE__, __FUNCTION__, __LINE__
 */
void	print_error_and_close_app(const char *file, const char *function,
		int line);

#endif
