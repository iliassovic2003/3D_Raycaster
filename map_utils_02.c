/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:23:52 by izahr             #+#    #+#             */
/*   Updated: 2025/08/24 02:23:53 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

static void	skip_offset(int fd, int offset)
{
	char	*line;
	int		i;

	i = 0;
	while (i < offset)
	{
		line = get_next_line(fd, 0);
		free(line);
		line = NULL;
		i++;
	}
}

static void	cleanup_static(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd, -1);
		if (line == NULL)
			break ;
		free(line);
	}
}

static void	check_line(t_mlx *mlx, char *line)
{
	char	*trimmed;

	if ((int)ft_strlen(line) > mlx->map.width)
	{
		trimmed = ft_strtrim(line);
		mlx->map.width = ft_strlen(trimmed);
		free(trimmed);
	}
}

int	read_map_dimensions(t_mlx *mlx, char *filename, int offset)
{
	int		fd;
	char	*line;

	fd = opening_file(mlx, filename);
	skip_offset(fd, offset);
	line = get_next_line(fd, 0);
	while (line != NULL)
	{
		if (!ft_strcmp(line, "\n"))
		{
			free(line);
			line = get_next_line(fd, 0);
			continue ;
		}
		check_line(mlx, line);
		mlx->map.height++;
		free(line);
		line = get_next_line(fd, 0);
	}
	cleanup_static(fd);
	close(fd);
	return (0);
}

int	fill_map_data(t_mlx *mlx, int fd, int offset)
{
	char	*line;
	int		map_line;
	int		flag;

	map_line = 0;
	flag = 0;
	skip_offset(fd, offset);
	line = get_next_line(fd, 0);
	while (line != NULL && map_line < mlx->map.height)
	{
		if (!ft_strcmp(line, "\n"))
		{
			free(line);
			line = get_next_line(fd, 0);
			continue ;
		}
		fill_map(line, mlx, map_line++, &flag);
		free(line);
		line = get_next_line(fd, 0);
	}
	cleanup_static(fd);
	return (flag);
}
