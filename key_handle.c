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

int key_press(int keycode, t_mlx *mlx)
{
    check_keycard_pickup(mlx);
    if (keycode == KEY_ESC)
        return (exit_program(mlx), 0);
    else if (keycode == KEY_TAB)
        cycle_keycards(mlx);
    else if (keycode == KEY_M)
        mlx->show_map = !mlx->show_map;
    else if (keycode == KEY_F && handle_doors(mlx))
        return (0);
    else if (keycode == KEY_W)
        mlx->keys.w = 1;
    else if (keycode == KEY_A)
        mlx->keys.a = 1;
    else if (keycode == KEY_S)
        mlx->keys.s = 1;
    else if (keycode == KEY_D)
        mlx->keys.d = 1;
    else if (keycode == KEY_LEFT)
        mlx->keys.left = 1;
    else if (keycode == KEY_RIGHT)
        mlx->keys.right = 1;
    return (0);
}

int key_release(int keycode, t_mlx *mlx)
{
    if (keycode == KEY_W)
        mlx->keys.w = 0;
    else if (keycode == KEY_A)
        mlx->keys.a = 0;
    else if (keycode == KEY_S)
        mlx->keys.s = 0;
    else if (keycode == KEY_D)
        mlx->keys.d = 0;
    else if (keycode == KEY_LEFT)
        mlx->keys.left = 0;
    else if (keycode == KEY_RIGHT)
        mlx->keys.right = 0;
    return (0);
}

void handle_movement(t_mlx *mlx)
{
    float move_speed = 0.02f;
    float rot_speed = 0.015f;
    t_move move;
    
    move.dx = 0;
    move.dy = 0;
    
    if (mlx->keys.w)
    {
        move.dx += mlx->player.dir_x * move_speed;
        move.dy += mlx->player.dir_y * move_speed;
    }
    if (mlx->keys.s)
    {
        move.dx -= mlx->player.dir_x * move_speed;
        move.dy -= mlx->player.dir_y * move_speed;
    }
    if (mlx->keys.d)
    {
        move.dx += mlx->player.plane_x * move_speed;
        move.dy += mlx->player.plane_y * move_speed;
    }
    if (mlx->keys.a)
    {
        move.dx -= mlx->player.plane_x * move_speed;
        move.dy -= mlx->player.plane_y * move_speed;
    }
    
    if (move.dx != 0 || move.dy != 0)
        move_player(mlx, &move, 0.1f);
        
    if (mlx->keys.right)
        rotate_player(mlx, rot_speed, 1);
    if (mlx->keys.left)
        rotate_player(mlx, rot_speed, 0);
}


