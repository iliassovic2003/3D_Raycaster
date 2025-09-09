/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:23:49 by izahr             #+#    #+#             */
/*   Updated: 2025/09/09 23:43:12 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

static void	set_player_direction(char *line, t_mlx *mlx, t_tmp2 tmp, int *flag)
{
	mlx->map.map2d[tmp.j][tmp.i] = '0';
	mlx->player.spawn_x = tmp.i;
	mlx->player.spawn_y = tmp.j;
	if (line[tmp.i] == 'N')
		mlx->player.spawn_angle = -M_PI / 2;
	else if (line[tmp.i] == 'E')
		mlx->player.spawn_angle = 0;
	else if (line[tmp.i] == 'S')
		mlx->player.spawn_angle = M_PI / 2;
	else if (line[tmp.i] == 'W')
		mlx->player.spawn_angle = M_PI;
	*flag = 1;
}

static void	set_door(t_tmp2 tmp, t_mlx *mlx, char type)
{
	if (type == 'n')
	{
		mlx->map.map2d[tmp.j][tmp.i] = '1';
		mlx->door.door_x = tmp.i;
		mlx->door.door_y = tmp.j;
	}
	else
	{
		mlx->map.map2d[tmp.j][tmp.i] = '1';
		mlx->exit_door.door_x = tmp.i;
		mlx->exit_door.door_y = tmp.j;
	}
}

static void	set_keycard(t_tmp2 tmp, t_mlx *mlx, char type)
{
	if (type == 'g')
	{
		mlx->map.map2d[tmp.j][tmp.i] = '0';
		mlx->green_keycard.x = tmp.i + 0.7;
		mlx->green_keycard.y = tmp.j + 0.5;
		mlx->green_keycard.visible = true;
	}
	else
	{
		mlx->map.map2d[tmp.j][tmp.i] = '0';
		mlx->white_keycard.x = tmp.i + 0.5;
		mlx->white_keycard.y = tmp.j + 0.5;
		mlx->white_keycard.visible = true;
	}
}

static void	fill_map_loop(char *line, t_mlx *mlx, t_tmp2 tmp, int *flag)
{
	while (tmp.i < (int)ft_strlen(line) && tmp.i < mlx->map.width)
	{
		if (line[tmp.i] == '0')
			mlx->map.map2d[tmp.j][tmp.i] = '0';
		else if (line[tmp.i] == ' ')
			mlx->map.map2d[tmp.j][tmp.i] = '-';
		else if (line[tmp.i] == '1')
			mlx->map.map2d[tmp.j][tmp.i] = '1';
		else if (line[tmp.i] == 'N' || line[tmp.i] == 'S' || line[tmp.i] == 'W'
			|| line[tmp.i] == 'E')
			set_player_direction(line, mlx, tmp, flag);
		else if (line[tmp.i] == '2')
			set_door(tmp, mlx, 'n');
		else if (line[tmp.i] == '3')
			set_door(tmp, mlx, 'e');
		else if (line[tmp.i] == 'G')
			set_keycard(tmp, mlx, 'g');
		else if (line[tmp.i] == 'Z')
			set_keycard(tmp, mlx, 'w');
		else if (line[tmp.i] == '\n')
			mlx->map.map2d[tmp.j][tmp.i] = '\0';
		else
			*flag = 2;
		tmp.i++;
	}
}

void	fill_map(char *line, t_mlx *mlx, int k, int *flag)
{
	t_tmp2	tmp;

	tmp.i = 0;
	tmp.j = k;
	fill_map_loop(line, mlx, tmp, flag);
}
