/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color_03.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 03:03:10 by izahr             #+#    #+#             */
/*   Updated: 2025/08/24 03:04:06 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

static void	set_ray(t_mlx *mlx, t_render_ray *ray, t_img **texture)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			*texture = &mlx->textures[2];
		else
			*texture = &mlx->textures[3];
	}
	else
	{
		if (ray->ray_dir_y > 0)
			*texture = &mlx->textures[1];
		else
			*texture = &mlx->textures[0];
	}
}

int	calculate_texture_x(t_mlx *mlx, t_render_ray *ray)
{
	double	wall_x;
	int		tex_x;
	t_img	*texture;

	set_ray(mlx, ray, &texture);
	if (ray->side == 0)
		wall_x = mlx->player.p_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = mlx->player.p_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)texture->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = texture->width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

int	calculate_texture_y(t_mlx *mlx, t_render_ray *ray, int y)
{
	int		tex_y;
	double	d;
	t_img	*texture;

	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			texture = &mlx->textures[2];
		else
			texture = &mlx->textures[3];
	}
	else
	{
		if (ray->ray_dir_y > 0)
			texture = &mlx->textures[1];
		else
			texture = &mlx->textures[0];
	}
	d = y - mlx->win_height / 2 + ray->line_height / 2;
	tex_y = (int)(d * texture->height / ray->line_height);
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	return (tex_y);
}

int	get_texture_pixel(t_mlx *mlx, t_render_ray *ray, int tex_x, int tex_y)
{
	t_img	*texture;
	int		*data;
	int		color;

	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			texture = &mlx->textures[2];
		else
			texture = &mlx->textures[3];
	}
	else
	{
		if (ray->ray_dir_y > 0)
			texture = &mlx->textures[1];
		else
			texture = &mlx->textures[0];
	}
	if (tex_x < 0 || tex_x >= texture->width || tex_y < 0
		|| tex_y >= texture->height)
		return (0);
	data = (int *)texture->img_data;
	color = data[tex_y * texture->width + tex_x];
	return (color);
}
