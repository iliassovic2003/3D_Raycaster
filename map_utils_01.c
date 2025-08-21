#include "Cub3D.h"
#include <stddef.h>

int	init_map(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	mlx->map.map2D = (char **)malloc(sizeof(char *) * mlx->map.height);
	if (!mlx->map.map2D)
		return (1);
	while (i < mlx->map.height)
	{
		mlx->map.map2D[i] = (char *)malloc(sizeof(char) * mlx->map.width);
		if (!mlx->map.map2D[i])
		{
			while (--i >= 0)
				free(mlx->map.map2D[i]);
			free(mlx->map.map2D);
			return (1);
		}
		j = 0;
		while (j < mlx->map.width)
		{
			mlx->map.map2D[i][j] = '-';
			j++;
		}
		i++;
	}
	return (0);
}

void	fill_map(char *line, t_mlx *mlx, int k, int *flag)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(line) && i < mlx->map.width)
	{
		if (line[i] == '0')
			mlx->map.map2D[k][i] = '0';
		else if (line[i] == ' ')
			mlx->map.map2D[k][i] = '-';
		else if (line[i] == '1')
			mlx->map.map2D[k][i] = '1';
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
				|| line[i] == 'E')
		{
			mlx->map.map2D[k][i] = '0';
			mlx->player.spawn_x = i;
			mlx->player.spawn_y = k;
			if (line[i] == 'N')
				mlx->player.spawn_angle = -M_PI / 2;
			else if (line[i] == 'E')
				mlx->player.spawn_angle = 0;
			else if (line[i] == 'S')
				mlx->player.spawn_angle = M_PI / 2;
			else if (line[i] == 'W')
				mlx->player.spawn_angle = M_PI;
			*flag = 1;
		}
		else if (line[i] == '2')
		{
			mlx->map.map2D[k][i] = '1';
			mlx->door.door_x = i;
			mlx->door.door_y = k;
		}
		else if (line[i] == '3')
		{
			mlx->map.map2D[k][i] = '1';
			mlx->exit_door.door_x = i;
			mlx->exit_door.door_y = k;
		}
		else if (line[i] == 'G')
		{
			mlx->map.map2D[k][i] = '0';
			mlx->green_keycard.x = i + 0.7;
			mlx->green_keycard.y = k + 0.5;
			mlx->green_keycard.visible = true;
		}
		else if (line[i] == 'Z')
		{
			mlx->map.map2D[k][i] = '0';
			mlx->white_keycard.x = i + 0.5;
			mlx->white_keycard.y = k + 0.5;
			mlx->white_keycard.visible = true;
		}
		else if (line[i] == '\n')
			;
		else
			*flag = 2;
		i++;
	}
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
			if (mlx.map.map2D[i][j] == '0' && (!mlx.map.map2D[i][j + 1] || mlx.map.map2D[i][j + 1] == '-'))
				return (1);
			if (mlx.map.map2D[i][j] == '0' && (!mlx.map.map2D[i + 1][j] || mlx.map.map2D[i + 1][j] == '-'))
				return (1);
			if (mlx.map.map2D[i][j] == '0' && (!mlx.map.map2D[i][j - 1] || mlx.map.map2D[i][j - 1] == '-'))
				return (1);
			if (mlx.map.map2D[i][j] == '0' && (!mlx.map.map2D[i - 1][j] || mlx.map.map2D[i - 1][j] == '-'))
				return (1);
			j++;
		}
	}
	return (0);
}
