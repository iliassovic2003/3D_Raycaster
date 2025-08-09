#include "Cub3D.h"

void	initialize_sprite_data(t_mlx *mlx, t_sprite_data *data)
{
	float	dx;
	float	dy;

	data->sprite_count = 0;
	data->float_offset = sinf(mlx->animation_timer) * 0.1f;
	if (mlx->green_keycard.visible)
	{
		data->sprites[data->sprite_count] = &mlx->green_keycard;
		dx = mlx->player.p_x - mlx->green_keycard.x;
		dy = mlx->player.p_y - mlx->green_keycard.y;
		data->sprite_distances[data->sprite_count] = dx * dx + dy * dy;
		data->sprite_count++;
	}
	if (mlx->white_keycard.visible)
	{
		data->sprites[data->sprite_count] = &mlx->white_keycard;
		dx = mlx->player.p_x - mlx->white_keycard.x;
		dy = mlx->player.p_y - mlx->white_keycard.y;
		data->sprite_distances[data->sprite_count] = dx * dx + dy * dy;
		data->sprite_count++;
	}
}

void	sort_sprites(t_sprite_data *data)
{
	int			i;
	int			j;
	float		temp_dist;
	t_sprite	*temp_sprite;

	i = 0;
	while (i < data->sprite_count)
	{
		j = i + 1;
		while (j < data->sprite_count)
		{
			if (data->sprite_distances[i] < data->sprite_distances[j])
			{
				temp_dist = data->sprite_distances[i];
				data->sprite_distances[i] = data->sprite_distances[j];
				data->sprite_distances[j] = temp_dist;
				temp_sprite = data->sprites[i];
				data->sprites[i] = data->sprites[j];
				data->sprites[j] = temp_sprite;
			}
			j++;
		}
		i++;
	}
}
