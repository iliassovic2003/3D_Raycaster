#include "Cub3D.h"

static void	locked_door(t_mlx *mlx, int door_x, int door_y)
{
	if (mlx->player.has_green_keycard && mlx->player.is_holding_keycard
		&& mlx->player.holding_keycard_type == 1)
	{
		mlx->door.is_locked = 0;
		mlx->map.map2D[door_y][door_x] = '0';
		printf("You unlock the door with the Green Keycard!\n");
	}
	else if (mlx->player.has_green_keycard)
		printf("You need to equip the Green Keycard first! (Press TAB)\n");
	else
		printf("This door requires a Green Keycard.\n");
}

static void	open_door(t_mlx *mlx, int door_x, int door_y)
{
	int	player_x;
	int	player_y;

	player_x = (int)mlx->player.p_x;
	player_y = (int)mlx->player.p_y;
	if (mlx->map.map2D[door_y][door_x] == '0')
	{
		if (player_x != door_x || player_y != door_y)
		{
			mlx->map.map2D[door_y][door_x] = '1';
			printf("Door closed with Green Keycard\n");
		}
		else
			printf("Cannot close door while standing on it!\n");
	}
	else
	{
		mlx->map.map2D[door_y][door_x] = '0';
		printf("Door opened with Green Keycard\n");
	}
}

static int	handle_green_door(t_mlx *mlx, float door_dist)
{
	int	door_x;
	int	door_y;

	if (door_dist >= 2.0)
		return (0);
	door_x = (int)mlx->door.door_x;
	door_y = (int)mlx->door.door_y;
	if (mlx->door.is_locked)
		locked_door(mlx, door_x, door_y);
	else if (mlx->player.is_holding_keycard
			&& mlx->player.holding_keycard_type == 1)
		open_door(mlx, door_x, door_y);
	else
		printf("You need to equip the Green Keycard to operate this door.\n");
	return (0);
}

static int	handle_exit_door(t_mlx *mlx, float exit_dist)
{
	if (exit_dist >= 2.0)
		return (0);
	if (mlx->exit_door.is_locked)
	{
		if (mlx->player.has_white_keycard && mlx->player.is_holding_keycard
			&& mlx->player.holding_keycard_type == 2)
		{
			mlx->exit_door.is_locked = 0;
			printf("You unlock the exit with the White Keycard!\n");
		}
		else if (mlx->player.has_white_keycard)
			printf("You need to equip the White Keycard first! (Press TAB)\n");
		else
			printf("This exit requires a White Keycard.\n");
	}
	else if (mlx->player.is_holding_keycard
			&& mlx->player.holding_keycard_type == 2)
	{
		printf("Congratulations! You've escaped!\n");
		exit_program(mlx);
		return (1);
	}
	else
		printf("You need to equip the White Keycard to use this exit.\n");
	return (0);
}

int	handle_doors(t_mlx *mlx)
{
	t_tmp3	tmp;

	tmp.door_dist_x = mlx->door.door_x - mlx->player.p_x;
	tmp.door_dist_y = mlx->door.door_y - mlx->player.p_y;
	tmp.door_dist = sqrt(tmp.door_dist_x * tmp.door_dist_x + tmp.door_dist_y
			* tmp.door_dist_y);
	handle_green_door(mlx, tmp.door_dist);
	tmp.exit_dist_x = mlx->exit_door.door_x - mlx->player.p_x;
	tmp.exit_dist_y = mlx->exit_door.door_y - mlx->player.p_y;
	tmp.exit_dist = sqrt(tmp.exit_dist_x * tmp.exit_dist_x + tmp.exit_dist_y
			* tmp.exit_dist_y);
	return (handle_exit_door(mlx, tmp.exit_dist));
}
