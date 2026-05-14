/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:23:29 by izahr             #+#    #+#             */
/*   Updated: 2025/09/09 23:27:24 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	free_map(t_mlx *mlx)
{
	int	y;

	y = 0;
	if (!mlx->map.map2d)
		return ;
	while (y < mlx->map.height)
	{
		free(mlx->map.map2d[y]);
		y++;
	}
	free(mlx->map.map2d);
}

static void	free_resv2(t_mlx *mlx)
{
	if (mlx->green_keycard.texture.img_ptr)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->green_keycard.texture.img_ptr);
		mlx->green_keycard.texture.img_ptr = NULL;
		mlx->green_keycard.texture.img_data = NULL;
	}
	if (mlx->white_keycard.texture.img_ptr)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->white_keycard.texture.img_ptr);
		mlx->white_keycard.texture.img_ptr = NULL;
		mlx->white_keycard.texture.img_data = NULL;
	}
	if (mlx->door.texture.img_ptr)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->door.texture.img_ptr);
		mlx->door.texture.img_ptr = NULL;
		mlx->door.texture.img_data = NULL;
	}
	if (mlx->exit_door.texture.img_ptr)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->exit_door.texture.img_ptr);
		mlx->exit_door.texture.img_ptr = NULL;
		mlx->exit_door.texture.img_data = NULL;
	}
}

static void	free_textures(t_mlx *mlx)
{
	int	i;

	i = 0;
	if (!mlx || !mlx->mlx_ptr)
		return ;
	while (i < 4)
	{
		if (mlx->textures[i].img_ptr)
			mlx_destroy_image(mlx->mlx_ptr, mlx->textures[i].img_ptr);
		i++;
	}
}

void	free_res(int fd, t_mlx *mlx, char *line)
{
	if (line)
		free(line);
	if (fd > 0)
		close(fd);
	if (!mlx || !mlx->mlx_ptr)
		return ;
	free_textures(mlx);
	free_resv2(mlx);
	free_map(mlx);
	if (mlx->win_ptr && mlx->mlx_ptr)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->img.img_ptr && mlx->mlx_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	if (mlx->mlx_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
	}
}
