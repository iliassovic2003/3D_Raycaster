#include "Cub3D.h"

static void	draw_keycard(t_mlx *mlx, t_sprite sprite, int size, int color)
{
	int		card_size;
	t_tmp2	tmp;

	tmp.x = 10 + (int)(sprite.x * size);
	tmp.y = 10 + (int)(sprite.y * size);
	card_size = size / 3;
	if (card_size < 2)
		card_size = 2;
	tmp.i = 0;
	while (tmp.i < card_size)
	{
		tmp.j = 0;
		while (tmp.j < card_size)
		{
			put_pixel_to_img(mlx, tmp.x + tmp.i - card_size / 2, tmp.y + tmp.j
					- card_size / 2, color);
			tmp.j++;
		}
		tmp.i++;
	}
}

void	draw_minimap_keycards(t_mlx *mlx, t_mini_data *data)
{
	if (mlx->green_keycard.visible)
		draw_keycard(mlx, mlx->green_keycard, data->tile_size, 0x00FF00);
	if (mlx->white_keycard.visible)
		draw_keycard(mlx, mlx->white_keycard, data->tile_size, 0xFF0000);
}

static void	draw_player_dot(t_mlx *mlx, t_tmp2 tmp, int player_size)
{
	int	i;
	int	j;

	i = -player_size / 2;
	while (i < player_size / 2)
	{
		j = -player_size / 2;
		while (j < player_size / 2)
		{
			put_pixel_to_img(mlx, tmp.x + i, tmp.y + j, 0xFF0000);
			j++;
		}
		i++;
	}
}

static void	draw_direction_line(t_mlx *mlx, t_tmp2 tmp)
{
	t_tmp2	tmp2;
	float	x;
	float	y;
	int		i;

	tmp2.x = tmp.i - tmp.x;
	tmp2.y = tmp.j - tmp.y;
	tmp.i = abs(tmp2.x) > abs(tmp2.y) ? abs(tmp2.x) : abs(tmp2.y);
	tmp2.fx = tmp2.x / (float)tmp.i;
	tmp2.fy = tmp2.y / (float)tmp.i;
	x = tmp.x;
	y = tmp.y;
	i = 0;
	while (i < tmp.i)
	{
		put_pixel_to_img(mlx, (int)x, (int)y, 0xFF0000);
		x += tmp2.fx;
		y += tmp2.fy;
		i++;
	}
}

void	draw_minimap_player(t_mlx *mlx, t_mini_data *data)
{
	t_tmp2	tmp;
	int		player_size;

	tmp.x = 10 + (int)(mlx->player.p_x * data->tile_size);
	tmp.y = 10 + (int)(mlx->player.p_y * data->tile_size);
	player_size = data->tile_size / 3;
	if (player_size < 2)
		player_size = 2;
	draw_player_dot(mlx, tmp, player_size);
	tmp.i = tmp.x + (int)(mlx->player.dir_x * data->tile_size);
	tmp.j = tmp.y + (int)(mlx->player.dir_y * data->tile_size);
	draw_direction_line(mlx, tmp);
}
