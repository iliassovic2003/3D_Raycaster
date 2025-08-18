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
	int	*data;
	int	pixel;

	if (x < 0 || y < 0 || x >= texture->width || y >= texture->height)
		return (0);
	data = (int *)texture->img_data;
	pixel = data[y * texture->width + x];
	return (pixel);
}

static unsigned int	color_to_int(t_color color)
{
	return ((color.R * 256 * 256) + (color.G * 256) + color.B);
}

void	draw_floor(t_mlx *mlx, t_render_ray *ray, int x)
{
	int				y;
	unsigned int	floor_color;

	floor_color = color_to_int(mlx->floor);
	y = ray->draw_end;
	while (y < mlx->win_height)
	{
		put_pixel_to_img(mlx, x, y, floor_color);
		y++;
	}
}

void	draw_ceiling(t_mlx *mlx, t_render_ray *ray, int x)
{
	int				y;
	unsigned int	ceiling_color;

	ceiling_color = color_to_int(mlx->ceiling);
	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel_to_img(mlx, x, y, ceiling_color);
		y++;
	}
}
