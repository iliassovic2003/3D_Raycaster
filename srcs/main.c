/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:23:46 by izahr             #+#    #+#             */
/*   Updated: 2025/09/09 23:43:33 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

static int	print_free(char *msg, int fd, t_mlx *mlx)
{
	if (fd != -1)
		close(fd);
	if (msg)
		printf("%s", msg);
	free_res(0, mlx, NULL);
	return (1);
}

int	read_map_content(t_mlx *mlx, char *filename, int offset)
{
	int	fd;
	int	flag;

	fd = opening_file(mlx, filename);
	if (init_map(mlx))
		return (print_free(NULL, fd, mlx));
	flag = fill_map_data(mlx, fd, offset);
	close(fd);
	if (flag == 0)
		return (print_free("Map Error: No Player's Coordinates\n", -1, mlx));
	else if (flag == 2)
		return (print_free("Map Error: Bad Configuration\n", -1, mlx));
	if (check_map(*mlx))
		return (print_free("Map Error: Incomplete walls\n", -1, mlx));
	return (0);
}

void	init_game_state(t_mlx *mlx)
{
	ft_bzero(mlx, sizeof(t_mlx));
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		exit(1);
	mlx->door.is_locked = 1;
	mlx->door.key_type = 1;
	mlx->exit_door.is_locked = 1;
	mlx->exit_door.key_type = 2;
	mlx->exit_door.door_x = -1;
	mlx->exit_door.door_y = -1;
	mlx->door.door_x = -1;
	mlx->door.door_y = -1;
	mlx->floor.r = -1;
	mlx->ceiling.r = -1;
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
