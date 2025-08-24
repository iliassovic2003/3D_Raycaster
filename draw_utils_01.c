/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:23:07 by izahr             #+#    #+#             */
/*   Updated: 2025/08/24 02:23:08 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	draw_hollow_square(t_mlx *mlx, t_tmp1 tmp)
{
	int	i;

	i = 0;
	while (i < tmp.size)
	{
		put_pixel_to_img(mlx, tmp.x + i, tmp.y, tmp.color);
		put_pixel_to_img(mlx, tmp.x + i, tmp.y + tmp.size - 1, tmp.color);
		i++;
	}
	i = 0;
	while (i < tmp.size)
	{
		put_pixel_to_img(mlx, tmp.x, tmp.y + i, tmp.color);
		put_pixel_to_img(mlx, tmp.x + tmp.size - 1, tmp.y + i, tmp.color);
		i++;
	}
}

static void	drawing_keycard(t_mlx *mlx, int x_pos, int y_pos, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < 30)
	{
		x = -1;
		while (++x < 50)
			put_pixel_to_img(mlx, x_pos + x, y_pos + y, color);
		y++;
	}
	x = 0;
	while (x < 50)
	{
		put_pixel_to_img(mlx, x_pos + x, y_pos, 0x000000);
		put_pixel_to_img(mlx, x_pos + x, y_pos + 29, 0x000000);
		x++;
	}
	y = 0;
	while (y < 30)
	{
		put_pixel_to_img(mlx, x_pos, y_pos + y, 0x000000);
		put_pixel_to_img(mlx, x_pos + 49, y_pos + y, 0x000000);
		y++;
	}
}

void	draw_held_keycard(t_mlx *mlx)
{
	int	x_pos;
	int	y_pos;
	int	keycard_color;

	if (!mlx->player.is_holding_keycard)
		return ;
	if (mlx->player.holding_keycard_type == 1)
		keycard_color = 0x00FF00;
	else if (mlx->player.holding_keycard_type == 2)
		keycard_color = 0xFFFFFF;
	else
		return ;
	x_pos = mlx->win_width - 70;
	y_pos = mlx->win_height - 50;
	drawing_keycard(mlx, x_pos, y_pos, keycard_color);
}
