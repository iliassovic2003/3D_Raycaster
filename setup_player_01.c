#include "Cub3D.h"

static int	load_normal_door(t_mlx *mlx, int width, int height)
{
	if (!mlx->door.texture.img_ptr)
	{
		printf("Error loading door texture: ./textures/door.xpm\n");
		mlx->door.texture.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
															"./textures/door2.xpm",
															&width,
															&height);
		if (!mlx->door.texture.img_ptr)
		{
			printf("Error loading alternative door texture \n");
			return (1);
		}
	}
	mlx->door.texture.width = width;
	mlx->door.texture.height = height;
	mlx->door.texture.img_data = mlx_get_data_addr(
		mlx->door.texture.img_ptr,
		&mlx->door.texture.bits_per_pixel,
		&mlx->door.texture.line_length,
		&mlx->door.texture.endian);
	return (0);
}

static int	load_exit_door(t_mlx *mlx, int width, int height)
{
	if (!mlx->exit_door.texture.img_ptr)
	{
		printf("Error loading exit door texture\n");
		mlx_destroy_image(mlx->mlx_ptr, mlx->door.texture.img_ptr);
		mlx->exit_door.texture.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
																"textures/door.xpm",
																&width,
																&height);
		if (!mlx->exit_door.texture.img_ptr)
		{
			printf("Error loading exit door texture with alternative path\n");
			return (1);
		}
	}
	mlx->exit_door.texture.width = width;
	mlx->exit_door.texture.height = height;
	mlx->exit_door.texture.img_data = mlx_get_data_addr(
		mlx->exit_door.texture.img_ptr,
		&mlx->exit_door.texture.bits_per_pixel,
		&mlx->exit_door.texture.line_length,
		&mlx->exit_door.texture.endian);
	return (0);
}

static int	load_doors_texture(t_mlx *mlx)
{
	int	width;
	int	height;

	mlx->door.texture.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
														"./textures/door.xpm",
														&width,
														&height);
	if (load_normal_door(mlx, width, height))
		return (1);
	mlx->exit_door.texture.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
															"./textures/door1.xpm",
															&width,
															&height);
	if (load_exit_door(mlx, width, height))
		return (1);
	return (0);
}

static void	setup_player(t_mlx *mlx)
{
	mlx->player.p_x = (float)mlx->player.spawn_x + 0.5f;
	mlx->player.p_y = (float)mlx->player.spawn_y + 0.5f;
	mlx->player.angle = mlx->player.spawn_angle;
	mlx->animation_timer = 0.0f;
	mlx->player.dir_x = cos(mlx->player.angle);
	mlx->player.dir_y = sin(mlx->player.angle);
	mlx->player.plane_x = -mlx->player.dir_y * 0.66;
	mlx->player.plane_y = mlx->player.dir_x * 0.66;
}

int	setup_player_and_window(t_mlx *mlx)
{
	mlx->win_height = 720;
	mlx->win_width = 1080;
	setup_player(mlx);
	if (load_keycard_textures(mlx))
	{
		free_res(0, mlx, NULL);
		return (1);
	}
	if (load_doors_texture(mlx))
	{
		free_res(0, mlx, NULL);
		return (1);
	}
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->win_width, mlx->win_height,
			"Nein Schainder");
	if (!mlx->win_ptr)
		return (1);
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->win_width,
			mlx->win_height);
	mlx->img.img_data = mlx_get_data_addr(mlx->img.img_ptr,
			&mlx->img.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
	return (0);
}
