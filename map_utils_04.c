/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_04.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:24:00 by izahr             #+#    #+#             */
/*   Updated: 2025/08/24 02:24:01 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

int	init_map(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	mlx->map.map2d = (char **)malloc(sizeof(char *) * mlx->map.height);
	if (!mlx->map.map2d)
		return (1);
	while (i < mlx->map.height)
	{
		mlx->map.map2d[i] = (char *)malloc(sizeof(char) * mlx->map.width);
		if (!mlx->map.map2d[i])
		{
			while (--i >= 0)
				free(mlx->map.map2d[i]);
			free(mlx->map.map2d);
			return (1);
		}
		j = -1;
		while (++j < mlx->map.width)
			mlx->map.map2d[i][j] = '-';
		i++;
	}
	return (0);
}

int	check_map(t_mlx mlx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mlx.map.height)
	{
		j = 0;
		while (j < mlx.map.width)
		{
			if (mlx.map.map2d[i][j] == '0' && (!mlx.map.map2d[i][j + 1]
					|| mlx.map.map2d[i][j + 1] == '-'))
				return (1);
			if (mlx.map.map2d[i][j] == '0' && (!mlx.map.map2d[i + 1][j]
					|| mlx.map.map2d[i + 1][j] == '-'))
				return (1);
			if (mlx.map.map2d[i][j] == '0' && (!mlx.map.map2d[i][j - 1]
					|| mlx.map.map2d[i][j - 1] == '-'))
				return (1);
			if (mlx.map.map2d[i][j] == '0' && (!mlx.map.map2d[i - 1][j]
					|| mlx.map.map2d[i - 1][j] == '-'))
				return (1);
			j++;
		}
	}
	return (0);
}

int	opening_file(t_mlx *mlx, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening file\n");
		exit_program(mlx);
		exit(1);
	}
	return (fd);
}
