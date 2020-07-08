#include "wolf3d.h"

void	print_map(char *map, t_point map_size)
{
	int i, j;

	i = 0;
	while (i < map_size.y)
	{
		j = 0;
		while (j < map_size.x)
		{
			write(1, &map[i * map_size.x + j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}