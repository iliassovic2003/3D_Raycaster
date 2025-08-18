#include "Cub3D.h"

int	read_map_content(t_mlx *mlx, char *filename, int offset)
{
	int	fd;
	int	flag;

	fd = opening_file(mlx, filename);
	if (init_map(mlx))
	{
		close(fd);
		free_res(0, mlx, NULL);
		return (1);
	}
	flag = fill_map_data(mlx, fd, offset);
	close(fd);
	if (flag == 0)
	{
		printf("no coordinates for player, aborting\n");
		free_res(0, mlx, NULL);
		return (1);
	}
	if (check_map(*mlx))
	{
		free_res(0, mlx, NULL);
		printf("Map Error: Incomplete walls\n");
		return (1);
	}
	return (0);
}

static int	mouse_move(int x, int y, t_mlx *mlx)
{
	t_tmp2		tmp;
	static int	last_x;

	(void)y;
	tmp.x = x - last_x;
	last_x = mlx->win_height / 2;
	if (abs(tmp.x) > 2)
	{
		tmp.fi = tmp.x * 0.0004f;
		tmp.fj = mlx->player.dir_x;
		mlx->player.dir_x = mlx->player.dir_x * cos(tmp.fi) - mlx->player.dir_y
			* sin(tmp.fi);
		mlx->player.dir_y = tmp.fj * sin(tmp.fi) + mlx->player.dir_y
			* cos(tmp.fi);
		tmp.fx = mlx->player.plane_x;
		mlx->player.plane_x = mlx->player.plane_x * cos(tmp.fi)
			- mlx->player.plane_y * sin(tmp.fi);
		mlx->player.plane_y = tmp.fx * sin(tmp.fi) + mlx->player.plane_y
			* cos(tmp.fi);
		mlx->player.angle += tmp.fi;
		while (mlx->player.angle < 0)
			mlx->player.angle += 2 * M_PI;
		while (mlx->player.angle > 2 * M_PI)
			mlx->player.angle -= 2 * M_PI;
		mlx_mouse_move(mlx->mlx_ptr, mlx->win_ptr, mlx->win_height / 2,
				mlx->win_width / 2);
		usleep(800);
		render_3d_view(mlx);
	}
	return (0);
}

int	setup_hooks_and_start(t_mlx *mlx)
{
	render_3d_view(mlx);
	mlx_hook(mlx->win_ptr, 2, 1L << 0, key_press, mlx);
	mlx_hook(mlx->win_ptr, 3, 1L << 1, key_release, mlx);
	mlx_hook(mlx->win_ptr, 6, 1L << 6, mouse_move, mlx);
	mlx_mouse_move(mlx->mlx_ptr, mlx->win_ptr, mlx->win_height / 2,
			mlx->win_width / 2);
	mlx_hook(mlx->win_ptr, 17, 0, exit_program, mlx);
	mlx_loop_hook(mlx->mlx_ptr, game_loop, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}

void	init_game_state(t_mlx *mlx)
{
	ft_bzero(mlx, sizeof(t_mlx));
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		exit(1);
	mlx->map.width = 0;
	mlx->map.height = 0;
	mlx->door.open_state = 0;
	mlx->door.is_locked = 1;
	mlx->door.key_type = 1;
	mlx->exit_door.open_state = 0;
	mlx->exit_door.is_locked = 1;
	mlx->exit_door.key_type = 2;
	mlx->player.has_green_keycard = 0;
	mlx->player.has_white_keycard = 0;
	mlx->player.is_holding_keycard = 0;
	mlx->player.holding_keycard_type = 0;
	mlx->show_map = 0;
	mlx->keys.w = 0;
	mlx->keys.a = 0;
	mlx->keys.s = 0;
	mlx->keys.d = 0;
	mlx->keys.left = 0;
	mlx->keys.right = 0;
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	int		offset;

	if (argc != 2 || !ft_strstr(argv[1], ".cub"))
	{
		printf("Invalid Input; ./Cub3D <filename>.cub \n");
		return (1);
	}
	init_game_state(&mlx);
	offset = 2;
	first_pass(argv, &mlx, &offset);
	if (read_map_dimensions(&mlx, argv[1], offset) != 0)
		return (1);
	if (read_map_content(&mlx, argv[1], offset) != 0)
		return (1);
	if (setup_player_and_window(&mlx) != 0)
		return (1);
	return (setup_hooks_and_start(&mlx));
}
