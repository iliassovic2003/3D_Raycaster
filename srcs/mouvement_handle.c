/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:24:08 by izahr             #+#    #+#             */
/*   Updated: 2025/08/24 02:42:48 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

static void	angle_modifier(t_mlx *mlx, float rot_step, int direction)
{
	if (direction == 0)
	{
		mlx->player.angle -= rot_step;
		if (mlx->player.angle < 0)
			mlx->player.angle += 2 * M_PI;
	}
	else
	{
		mlx->player.angle += rot_step;
		if (mlx->player.angle > 2 * M_PI)
			mlx->player.angle -= 2 * M_PI;
	}
}

void	rotate_player(t_mlx *mlx, float rot_step, int direction)
{
	float	old_dir_x;
	float	old_plane_x;
	float	rotation;

	rotation = rot_step;
	if (direction == 0)
		rotation = -rot_step;
	old_dir_x = mlx->player.dir_x;
	mlx->player.dir_x = mlx->player.dir_x * cos(rotation) - mlx->player.dir_y
		* sin(rotation);
	mlx->player.dir_y = old_dir_x * sin(rotation) + mlx->player.dir_y
		* cos(rotation);
	old_plane_x = mlx->player.plane_x;
	mlx->player.plane_x = mlx->player.plane_x * cos(rotation)
		- mlx->player.plane_y * sin(rotation);
	mlx->player.plane_y = old_plane_x * sin(rotation) + mlx->player.plane_y
		* cos(rotation);
	angle_modifier(mlx, rot_step, direction);
}

static void	check_x_movement(t_mlx *mlx, t_move *move, float buffer)
{
	move->new_x = mlx->player.p_x + move->dx;
	move->map_x = (int)move->new_x;
	move->map_y = (int)mlx->player.p_y;
	move->can_move_x = 1;
	if (move->map_x < 0 || move->map_x >= mlx->map.width || move->map_y < 0
		|| move->map_y >= mlx->map.height)
	{
		move->can_move_x = 0;
		return ;
	}
	if (mlx->map.map2d[move->map_y][move->map_x] == '1')
		move->can_move_x = 0;
	else if (move->new_x - move->map_x > 1.0 - buffer && move->map_x
		+ 1 < mlx->map.width && mlx->map.map2d[move->map_y][move->map_x
		+ 1] == '1')
		move->new_x = move->map_x + 1.0 - buffer;
	else if (move->new_x - move->map_x < buffer && move->map_x > 0
		&& mlx->map.map2d[move->map_y][move->map_x - 1] == '1')
		move->new_x = move->map_x + buffer;
}

static void	check_y_movement(t_mlx *mlx, t_move *move, float buffer)
{
	move->new_y = mlx->player.p_y + move->dy;
	move->map_x = (int)mlx->player.p_x;
	if (move->can_move_x)
		move->map_x = (int)move->new_x;
	move->map_y = (int)move->new_y;
	move->can_move_y = 1;
	if (move->map_x < 0 || move->map_x >= mlx->map.width || move->map_y < 0
		|| move->map_y >= mlx->map.height)
	{
		move->can_move_y = 0;
		return ;
	}
	if (mlx->map.map2d[move->map_y][move->map_x] == '1')
		move->can_move_y = 0;
	else if (move->new_y - move->map_y > 1.0 - buffer && move->map_y
		+ 1 < mlx->map.height && mlx->map.map2d[move->map_y
			+ 1][move->map_x] == '1')
		move->new_y = move->map_y + 1.0 - buffer;
	else if (move->new_y - move->map_y < buffer && move->map_y > 0
		&& mlx->map.map2d[move->map_y - 1][move->map_x] == '1')
		move->new_y = move->map_y + buffer;
}

void	move_player(t_mlx *mlx, t_move *move, float buffer)
{
	if (move->dx == 0 && move->dy == 0)
		return ;
	check_x_movement(mlx, move, buffer);
	check_y_movement(mlx, move, buffer);
	if (move->can_move_x)
		mlx->player.p_x = move->new_x;
	if (move->can_move_y)
		mlx->player.p_y = move->new_y;
}
