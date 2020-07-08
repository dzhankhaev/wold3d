#include "wolf3d.h"

int main()
{
	char	*map;
	t_point	map_size;

	map = create_map("../maps/map1", &map_size);
	print_map(map, map_size);

	return (0);
}
