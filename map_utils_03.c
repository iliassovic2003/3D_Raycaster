/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_03.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:23:55 by izahr             #+#    #+#             */
/*   Updated: 2025/08/24 02:23:56 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

static void	still_exiting(t_mlx *mlx)
{
	if (mlx->img.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	if (mlx->win_ptr)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->mlx_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		mlx->mlx_ptr = NULL;
	}
	if (mlx->map.map2d)
		free_map(mlx);
}

int	exit_program(t_mlx *mlx)
{
	int	i;

	if (!mlx)
		exit(0);
	i = -1;
	while (++i < 4)
	{
		if (mlx->textures[i].img_ptr)
			mlx_destroy_image(mlx->mlx_ptr, mlx->textures[i].img_ptr);
	}
	if (mlx->green_keycard.texture.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->green_keycard.texture.img_ptr);
	if (mlx->white_keycard.texture.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->white_keycard.texture.img_ptr);
	if (mlx->door.texture.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->door.texture.img_ptr);
	if (mlx->exit_door.texture.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->exit_door.texture.img_ptr);
	still_exiting(mlx);
	exit(0);
}

static void	check_count(int count, char *line, t_mlx *mlx, int fd)
{
	if (count <= 4)
	{
		if (load_textures(line, mlx))
		{
			get_next_line(fd, -1);
			free_res(fd, mlx, line);
			exit(1);
		}
	}
	else if (count <= 6)
	{
		if (parse_color(line, mlx))
		{
			get_next_line(fd, -1);
			free_res(fd, mlx, line);
			exit(1);
		}
	}
	free(line);
	line = NULL;
}

static void	first_clean(char *line, int fd)
{
	if (line)
		free(line);
	line = get_next_line(fd, -1);
	close(fd);
}

void	first_pass(char **argv, t_mlx *mlx, int *offset)
{
	int		fd;
	int		count;
	char	*line;

	line = NULL;
	count = 0;
	fd = opening_file(mlx, argv[1]);
	line = get_next_line(fd, 0);
	while (line != NULL && count < 6)
	{
		if (!ft_strcmp(line, "\n"))
		{
			free(line);
			(*offset)++;
			line = get_next_line(fd, 0);
			continue ;
		}
		count++;
		check_count(count, line, mlx, fd);
		(*offset)++;
		line = get_next_line(fd, 0);
	}
	(*offset)--;
	first_clean(line, fd);
}
