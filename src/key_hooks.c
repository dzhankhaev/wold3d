#include "wolf3d.h"
#include "key_defines.h"

int				key_hooks(int key, void *temp)
{

	if (key == ESC)
		exit(0);
	else if (key == RIGHT)
		player_rot((t_all *)temp, PLAYER_ROTATE);
	else if (key == LEFT)
		player_rot((t_all *)temp, -PLAYER_ROTATE);
	else if (key == UP)
		player_step((t_all *)temp, PLAYER_STEP);
	else if (key == DOWN)
		player_step((t_all *)temp, -PLAYER_STEP);
	return (0);
}