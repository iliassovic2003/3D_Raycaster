#include "Cub3D.h"

static void	mini_dim(t_mlx *mlx, int width, int height, t_mini_data *data)
{
	int	tile_width;
	int	tile_height;

	tile_width = width / mlx->map.width;
	tile_height = height / mlx->map.height;
	data->tile_size = tile_width < tile_height ? tile_width : tile_height;
	if (data->tile_size < 1)
		data->tile_size = 1;
	data->actual_width = data->tile_size * mlx->map.width;
	data->actual_height = data->tile_size * mlx->map.height;
}

static void	draw_minimap_background(t_mlx *mlx, t_mini_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->actual_height)
	{
		x = 0;
		while (x < data->actual_width)
		{
			put_pixel_to_img(mlx, x + 10, y + 10, 0x333333);
			x++;
		}
		y++;
	}
}

static void	draw_minimap_walls(t_mlx *mlx, t_mini_data *data)
{
	int		x;
	int		y;
	t_tmp1	tmp;

	tmp.size = data->tile_size;
	tmp.color = 0xFFFFFF;
	y = 0;
	while (y < mlx->map.height)
	{
		x = 0;
		while (x < mlx->map.width)
		{
			tmp.x = 10 + x * data->tile_size;
			tmp.y = 10 + y * data->tile_size;
			if (mlx->map.map2D[y][x] == '1')
				draw_hollow_square(mlx, tmp);
			x++;
		}
		y++;
	}
}

static void	draw_minimap_doors(t_mlx *mlx, t_mini_data *data)
{
	t_tmp1	tmp;

	tmp.size = data->tile_size;
	tmp.x = 10 + (int)mlx->door.door_x * data->tile_size;
	tmp.y = 10 + (int)mlx->door.door_y * data->tile_size;
	tmp.color = 0x00FF00;
	draw_hollow_square(mlx, tmp);
	tmp.x = 10 + (int)mlx->exit_door.door_x * data->tile_size;
	tmp.y = 10 + (int)mlx->exit_door.door_y * data->tile_size;
	tmp.color = 0x0964f0;
	draw_hollow_square(mlx, tmp);
}

void	draw_minimap(t_mlx *mlx, int width, int height)
{
	t_mini_data	data;

	mini_dim(mlx, width, height, &data);
	draw_minimap_background(mlx, &data);
	draw_minimap_walls(mlx, &data);
	draw_minimap_keycards(mlx, &data);
	draw_minimap_doors(mlx, &data);
	draw_minimap_player(mlx, &data);
}
