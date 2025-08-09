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
	int		j;

	j = 0;
	i--;
	trimmed_path = ft_strtrim(line);
	mlx->textures[i].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, trimmed_path,
			&width, &height);
	if (!mlx->textures[i].img_ptr)
	{
		printf("Error loading texture: %s\n", line);
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
	if (!split_tmp[1])
		exit_error = 1;
	else if (!ft_strcmp(split_tmp[0], "NO"))
		exit_error = load_texture(split_tmp[1], mlx, 1);
	else if (!ft_strcmp(split_tmp[0], "SO"))
		exit_error = load_texture(split_tmp[1], mlx, 2);
	else if (!ft_strcmp(split_tmp[0], "WE"))
		exit_error = load_texture(split_tmp[1], mlx, 3);
	else if (!ft_strcmp(split_tmp[0], "EA"))
		exit_error = load_texture(split_tmp[1], mlx, 4);
	else
	{
		printf("Not Enough or Invalid Texture Data, Aborting... \n");
		exit_error = 1;
		free_arr(split_tmp);
	}
	free_arr(split_tmp);
	return (exit_error);
}
