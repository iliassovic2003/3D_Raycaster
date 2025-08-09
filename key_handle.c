#include "Cub3D.h"

static void	check_keycard_pickup(t_mlx *mlx)
{
	int	player_x;
	int	player_y;

	player_x = (int)mlx->player.p_x;
	player_y = (int)mlx->player.p_y;
	if (mlx->green_keycard.visible &&
		(int)mlx->green_keycard.x == player_x &&
		(int)mlx->green_keycard.y == player_y)
	{
		mlx->player.has_green_keycard = 1;
		mlx->green_keycard.visible = 0;
		printf("Picked up Green Keycard!\n");
		mlx->player.is_holding_keycard = 1;
		mlx->player.holding_keycard_type = 1;
	}
	if (mlx->white_keycard.visible &&
		(int)mlx->white_keycard.x == player_x &&
		(int)mlx->white_keycard.y == player_y)
	{
		mlx->player.has_white_keycard = 1;
		mlx->white_keycard.visible = 0;
		printf("Picked up White Keycard!\n");
		mlx->player.is_holding_keycard = 1;
		mlx->player.holding_keycard_type = 2;
	}
}

static void	cycle_keycards(t_mlx *mlx)
{
	if (!(mlx->player.has_green_keycard || mlx->player.has_white_keycard))
		return ;
	if (!mlx->player.is_holding_keycard)
	{
		if (mlx->player.has_green_keycard)
		{
			mlx->player.is_holding_keycard = 1;
			mlx->player.holding_keycard_type = 1;
		}
		else if (mlx->player.has_white_keycard)
		{
			mlx->player.is_holding_keycard = 1;
			mlx->player.holding_keycard_type = 2;
		}
	}
	else
	{
		if (mlx->player.holding_keycard_type == 1
			&& mlx->player.has_white_keycard)
			mlx->player.holding_keycard_type = 2;
		else if (mlx->player.holding_keycard_type == 2
				&& mlx->player.has_green_keycard)
			mlx->player.holding_keycard_type = 1;
		else
			mlx->player.is_holding_keycard = 0;
	}
	printf("Now holding keycard type: %d\n", mlx->player.holding_keycard_type);
}

static void	set_movement(t_mlx *mlx, t_move *move, int keycode, float step)
{
	move->dx = 0;
	move->dy = 0;
	if (keycode == KEY_W)
	{
		move->dx = mlx->player.dir_x * step;
		move->dy = mlx->player.dir_y * step;
	}
	else if (keycode == KEY_S)
	{
		move->dx = -mlx->player.dir_x * step;
		move->dy = -mlx->player.dir_y * step;
	}
	else if (keycode == KEY_A)
	{
		move->dx = -mlx->player.plane_x * step;
		move->dy = -mlx->player.plane_y * step;
	}
	else if (keycode == KEY_D)
	{
		move->dx = mlx->player.plane_x * step;
		move->dy = mlx->player.plane_y * step;
	}
}

int	handle_key(int keycode, t_mlx *mlx)
{
	float	move_step;
	float	rot_step;
	float	buffer;
	t_move	move;

	move_step = 0.1f;
	rot_step = 0.1f;
	buffer = 0.1f;
	check_keycard_pickup(mlx);
	if (keycode == KEY_TAB)
		cycle_keycards(mlx);
	else if (keycode == KEY_LEFT)
		rotate_player(mlx, rot_step, 0);
	else if (keycode == KEY_RIGHT)
		rotate_player(mlx, rot_step, 1);
	else if (keycode == KEY_ESC)
		return (exit_program(mlx), 0);
	else if (keycode == KEY_M)
		mlx->show_map = !mlx->show_map;
	else if (keycode == KEY_F && handle_doors(mlx))
		return (0);
	set_movement(mlx, &move, keycode, move_step);
	move_player(mlx, &move, buffer);
	return (render_3d_view(mlx), 0);
}
