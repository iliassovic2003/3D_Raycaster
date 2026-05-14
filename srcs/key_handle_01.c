/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:23:35 by izahr             #+#    #+#             */
/*   Updated: 2025/08/24 02:38:48 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

static void	check_keycard_pickup(t_mlx *mlx)
{
	int	player_x;
	int	player_y;

	player_x = (int)mlx->player.p_x;
	player_y = (int)mlx->player.p_y;
	if (mlx->green_keycard.visible
		&& (int)mlx->green_keycard.x == player_x
		&& (int)mlx->green_keycard.y == player_y)
	{
		mlx->player.has_green_keycard = 1;
		mlx->green_keycard.visible = 0;
		printf("Picked up Green Keycard!\n");
		mlx->player.is_holding_keycard = 1;
		mlx->player.holding_keycard_type = 1;
	}
	if (mlx->white_keycard.visible
		&& (int)mlx->white_keycard.x == player_x
		&& (int)mlx->white_keycard.y == player_y)
	{
		mlx->player.has_white_keycard = 1;
		mlx->white_keycard.visible = 0;
		printf("Picked up White Keycard!\n");
		mlx->player.is_holding_keycard = 1;
		mlx->player.holding_keycard_type = 2;
	}
}

static void	assign_first_available_keycard(t_mlx *mlx)
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

static void	cycle_keycards(t_mlx *mlx)
{
	if (!(mlx->player.has_green_keycard || mlx->player.has_white_keycard))
		return ;
	if (!mlx->player.is_holding_keycard)
		assign_first_available_keycard(mlx);
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
}

int	key_press(int keycode, t_mlx *mlx)
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
