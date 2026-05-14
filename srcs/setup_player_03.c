/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_player_03.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:24:24 by izahr             #+#    #+#             */
/*   Updated: 2025/09/09 02:21:54 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

static void	pickup_green(t_mlx *mlx)
{
	mlx->player.has_green_keycard = true;
	mlx->green_keycard.visible = false;
	printf("Picked up Green Keycard!\n");
	mlx->player.is_holding_keycard = true;
	mlx->player.holding_keycard_type = 1;
}

static void	pickup_white(t_mlx *mlx)
{
	mlx->player.has_white_keycard = true;
	mlx->white_keycard.visible = false;
	printf("Picked up White Keycard!\n");
	mlx->player.is_holding_keycard = true;
	mlx->player.holding_keycard_type = 2;
}

int	game_loop(t_mlx *mlx)
{
	int	player_tile_x;
	int	player_tile_y;

	player_tile_x = (int)mlx->player.p_x;
	player_tile_y = (int)mlx->player.p_y;
	mlx->animation_timer += 0.04f;
	if (mlx->animation_timer > 70.0f)
		mlx->animation_timer = 0.0f;
	if (mlx->green_keycard.visible
		&& (int)mlx->green_keycard.x == player_tile_x
		&& (int)mlx->green_keycard.y == player_tile_y)
		pickup_green(mlx);
	if (mlx->white_keycard.visible
		&& (int)mlx->white_keycard.x == player_tile_x
		&& (int)mlx->white_keycard.y == player_tile_y)
		pickup_white(mlx);
	handle_movement(mlx);
	render_3d_view(mlx);
	return (0);
}
