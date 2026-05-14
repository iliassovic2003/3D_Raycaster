/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color_01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:25:02 by izahr             #+#    #+#             */
/*   Updated: 2025/09/08 20:57:04 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

static int	is_digit(char *line)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (line[i])
	{
		if (line[i] == ',')
			k++;
		else if (line[i] != ',' && (line[i] < '0' || line[i] > '9'))
		{
			printf("Color Error: Misconfiguration Error\n");
			free(line);
			return (1);
		}
		i++;
	}
	if (k != 2)
	{
		printf("Color Error: Misconfiguration Error\n");
		free(line);
		return (1);
	}
	return (0);
}

static int	load_color_v2(int *r, int *g, int *b, char *line)
{
	char	**split_tmp;

	if (is_digit(line))
		return (1);
	split_tmp = ft_split(line, ',');
	free(line);
	if (!split_tmp || !split_tmp[0] || !split_tmp[1] || !split_tmp[2]
		|| split_tmp[3])
	{
		printf("Color Error: Misconfiguration Error\n");
		free_arr(split_tmp);
		return (1);
	}
	*r = ft_atoi(ft_strtrim(split_tmp[0]));
	*g = ft_atoi(ft_strtrim(split_tmp[1]));
	*b = ft_atoi(ft_strtrim(split_tmp[2]));
	free_arr(split_tmp);
	if (*r > 255 || *r < 0 || *g > 255 || *g < 0 || *b > 255 || *b < 0)
	{
		printf("Color Error: Range Error\n");
		return (1);
	}
	return (0);
}

static int	load_color(char *line, t_mlx *mlx, int i)
{
	int	r;
	int	g;
	int	b;

	if (load_color_v2(&r, &g, &b, line))
		return (1);
	if (i == 0)
	{
		mlx->floor.r = r;
		mlx->floor.g = g;
		mlx->floor.b = b;
	}
	else
	{
		mlx->ceiling.r = r;
		mlx->ceiling.g = g;
		mlx->ceiling.b = b;
	}
	return (0);
}

static void	printv2(char *msg, int *exit_error)
{
	if (msg)
		printf("%s", msg);
	*exit_error = 1;
}

int	parse_color(char *line, t_mlx *mlx)
{
	char	**split_tmp;
	int		exit_error;

	exit_error = 0;
	split_tmp = ft_split(line, ' ');
	if (!split_tmp || !split_tmp[0] || !split_tmp[1] || split_tmp[2])
		printv2("Color Error: Misconfiguration Error\n", &exit_error);
	else if (!ft_strcmp(split_tmp[0], "F") && mlx->floor.r == -1)
	{
		if (load_color(ft_strtrim(split_tmp[1]), mlx, 0))
			exit_error = 1;
	}
	else if (!ft_strcmp(split_tmp[0], "C") && mlx->ceiling.r == -1)
	{
		if (load_color(ft_strtrim(split_tmp[1]), mlx, 1))
			exit_error = 1;
	}
	else
		printv2("Color Error: Not Enough Data\n", &exit_error);
	free_arr(split_tmp);
	return (exit_error);
}
