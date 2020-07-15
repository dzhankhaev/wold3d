#include "wolf3d.h"
#include "key_defines.h"

int				loop_hooks(void *temp)
{
	t_pl	*player;

	player = ((t_all *)temp)->player;
	if (player->right == TRUE)
		player_rot((t_all *)temp, PLAYER_ROTATE);
	else if (player->left == TRUE)
		player_rot((t_all *)temp, -PLAYER_ROTATE);
	else if (player->up == TRUE)
		player_step((t_all *)temp, PLAYER_STEP);
	else if (player->down == TRUE)
		player_step((t_all *)temp, -PLAYER_STEP);
	return (0);
}

static void		player_keys(t_pl *player, int key)
{
	player->right = FALSE;
	player->left = FALSE;
	player->up = FALSE;
	player->down = FALSE;
	if (key == FALSE)
		return ;
	else if (key == RIGHT)
		player->right = TRUE;
	else if (key == LEFT)
		player->left = TRUE;
	else if (key == UP)
		player->up = TRUE;
	else if (key == DOWN)
		player->down = TRUE;
}

int				key_release(int key, void *player)
{
	if (key == RIGHT || key == LEFT || key == UP || key == DOWN)
		player_keys(((t_pl *)player), FALSE);
	return (0);
}

int				key_press(int key, void *player)
{
	if (key == ESC)
		exit(0);
	else if (key == RIGHT)
		player_keys(((t_pl *)player), RIGHT);
	else if (key == LEFT)
		player_keys(((t_pl *)player), LEFT);
	else if (key == UP)
		player_keys(((t_pl *)player), UP);
	else if (key == DOWN)
		player_keys(((t_pl *)player), DOWN);
	return (0);
}
