/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_player_02.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:24:19 by izahr             #+#    #+#             */
/*   Updated: 2025/08/24 02:46:19 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

static void	import_green_keycard(t_mlx *mlx, int width, int height)
{
	mlx->green_keycard.texture.width = width;
	mlx->green_keycard.texture.height = height;
	mlx->green_keycard.texture.img_data = mlx_get_data_addr(
			mlx->green_keycard.texture.img_ptr,
			&mlx->green_keycard.texture.bits_per_pixel,
			&mlx->green_keycard.texture.line_length,
			&mlx->green_keycard.texture.endian);
}

static void	import_white_keycard(t_mlx *mlx, int width, int height)
{
	mlx->white_keycard.texture.width = width;
	mlx->white_keycard.texture.height = height;
	mlx->white_keycard.texture.img_data = mlx_get_data_addr(
			mlx->white_keycard.texture.img_ptr,
			&mlx->white_keycard.texture.bits_per_pixel,
			&mlx->white_keycard.texture.line_length,
			&mlx->white_keycard.texture.endian);
}

int	load_keycard_textures(t_mlx *mlx)
{
	int	width;
	int	height;

	mlx->green_keycard.texture.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"./textures/keycard_green.xpm", &width, &height);
	if (!mlx->green_keycard.texture.img_ptr)
	{
		printf("Error loading green keycard texture\n");
		return (1);
	}
	import_green_keycard(mlx, width, height);
	mlx->white_keycard.texture.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
			"./textures/keycard_white.xpm", &width, &height);
	if (!mlx->white_keycard.texture.img_ptr)
	{
		printf("Error loading white keycard texture\n");
		mlx_destroy_image(mlx->mlx_ptr, mlx->green_keycard.texture.img_ptr);
		return (1);
	}
	import_white_keycard(mlx, width, height);
	return (0);
}
