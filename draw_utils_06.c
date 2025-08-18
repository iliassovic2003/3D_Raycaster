#include "Cub3D.h"

void	put_pixel_to_img(t_mlx *mlx, int x, int y, int color)
{
	int	offset;

	if (x >= 0 && x < mlx->win_width && y >= 0 && y < mlx->win_height)
	{
		offset = (y * mlx->img.line_length) + (x * (mlx->img.bits_per_pixel
					/ 8));
		*(unsigned int *)(mlx->img.img_data + offset) = color;
	}
}

unsigned int	get_pixel_color(t_img *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= texture->width || y >= texture->height)
		return (0);
	pixel = texture->img_data + (y * texture->line_length + x
			* (texture->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

static unsigned int	color_to_int(t_color color)
{
	return ((color.R * 256 * 256) + (color.G * 256) + color.B);
}

static void	draw_floor(t_mlx *mlx)
{
	int				x;
	int				y;
	unsigned int	floor_color;

	floor_color = color_to_int(mlx->floor);
	y = mlx->win_height / 2;
	while (y < mlx->win_height)
	{
		x = 0;
		while (x < mlx->win_width)
		{
			put_pixel_to_img(mlx, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void	draw_ceiling_floor(t_mlx *mlx)
{
	int				x;
	int				y;
	unsigned int	ceiling_color;

	ft_bzero(mlx->img.img_data, mlx->win_height * mlx->img.line_length);
	ceiling_color = color_to_int(mlx->ceiling);
	y = 0;
	while (y < mlx->win_height / 2)
	{
		x = 0;
		while (x < mlx->win_width)
		{
			put_pixel_to_img(mlx, x, y, ceiling_color);
			x++;
		}
		y++;
	}
	draw_floor(mlx);
}
