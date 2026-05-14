/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color_02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:25:06 by izahr             #+#    #+#             */
/*   Updated: 2025/09/08 20:39:59 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

static void	load_texture_error(t_mlx *mlx, char *trimmed, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->textures[j].img_ptr);
		mlx->textures[j].img_ptr = NULL;
		mlx->textures[j].img_data = NULL;
		j++;
	}
	free(trimmed);
}

static int	load_texture(char *line, t_mlx *mlx, int i)
{
	int		width;
	int		height;
	char	*trimmed_path;

	i--;
	trimmed_path = ft_strtrim(line);
	mlx->textures[i].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, trimmed_path,
			&width, &height);
	if (!mlx->textures[i].img_ptr)
	{
		printf("Error loading texture: %s", line);
		load_texture_error(mlx, trimmed_path, i);
		return (1);
	}
	mlx->textures[i].width = width;
	mlx->textures[i].height = height;
	mlx->textures[i].img_data = mlx_get_data_addr(mlx->textures[i].img_ptr,
			&mlx->textures[i].bits_per_pixel,
			&mlx->textures[i].line_length,
			&mlx->textures[i].endian);
	free(trimmed_path);
	return (0);
}

int	load_textures(char *line, t_mlx *mlx)
{
	char	**split_tmp;
	int		exit_error;

	exit_error = 0;
	split_tmp = ft_split(line, ' ');
	if (!split_tmp[1] || split_tmp[1][0] == '\n')
	{
		printf("Map Error: No Texture Was Given\n");
		exit_error = 1;
	}
	else if (!ft_strcmp(split_tmp[0], "NO") && !mlx->textures[0].img_ptr)
		exit_error = load_texture(split_tmp[1], mlx, 1);
	else if (!ft_strcmp(split_tmp[0], "SO") && !mlx->textures[1].img_ptr)
		exit_error = load_texture(split_tmp[1], mlx, 2);
	else if (!ft_strcmp(split_tmp[0], "WE") && !mlx->textures[2].img_ptr)
		exit_error = load_texture(split_tmp[1], mlx, 3);
	else if (!ft_strcmp(split_tmp[0], "EA") && !mlx->textures[3].img_ptr)
		exit_error = load_texture(split_tmp[1], mlx, 4);
	else
	{
		printf("Map Error: Not Enough Texture Data\n");
		exit_error = 1;
	}
	free_arr(split_tmp);
	return (exit_error);
}
