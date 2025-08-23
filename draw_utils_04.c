#include "Cub3D.h"

static void	choose_texture(t_mlx *mlx, t_render_ray *ray,
		t_texture_data *tex_data)
{
	int	tex_num;

	tex_data->is_door = (ray->map_x == (int)mlx->door.door_x
			&& ray->map_y == (int)mlx->door.door_y);
	tex_data->is_exit_door = (ray->map_x == (int)mlx->exit_door.door_x
			&& ray->map_y == (int)mlx->exit_door.door_y);
	if (tex_data->is_door)
		tex_data->texture = &mlx->door.texture;
	else if (tex_data->is_exit_door)
		tex_data->texture = &mlx->exit_door.texture;
	else
	{
		if (ray->side == 0)
			tex_num = (ray->ray_dir_x > 0) ? 2 : 3;
		else
			tex_num = (ray->ray_dir_y > 0) ? 1 : 0;
		tex_data->texture = &mlx->textures[tex_num];
	}
}

static void	calculate_texture_position(t_mlx *mlx, t_render_ray *ray,
		t_texture_data *tex_data)
{
	if (ray->side == 0)
		tex_data->wall_x = mlx->player.p_y + ray->perp_wall_dist
			* ray->ray_dir_y;
	else
		tex_data->wall_x = mlx->player.p_x + ray->perp_wall_dist
			* ray->ray_dir_x;
	tex_data->wall_x -= floor(tex_data->wall_x);
	tex_data->tex_x = (int)(tex_data->wall_x * tex_data->texture->width);
	if ((ray->side == 0 && ray->ray_dir_x < 0) || (ray->side == 1
			&& ray->ray_dir_y > 0))
		tex_data->tex_x = tex_data->texture->width - tex_data->tex_x - 1;
	if (tex_data->tex_x < 0)
		tex_data->tex_x = 0;
	if (tex_data->tex_x >= tex_data->texture->width)
		tex_data->tex_x = tex_data->texture->width - 1;
		
	tex_data->step = (float)tex_data->texture->height / ray->line_height;
	tex_data->tex_pos = (ray->draw_start - (int)(mlx->win_height / 2)
			+ (int)(ray->line_height / 2)) * tex_data->step;
}

static void	draw_textured_wall(t_mlx *mlx, t_render_ray *ray,
		t_texture_data *tex_data, int x)
{
	int				y;
	int				tex_x;
	int				tex_y;
	unsigned int	color;

	y = ray->draw_start  -1;
	while (++y < ray->draw_end)
	{
		if (tex_data->is_door || tex_data->is_exit_door)
		{
			tex_x = tex_data->tex_x;
			tex_y = (int)tex_data->tex_pos & (tex_data->texture->height - 1);
			tex_data->tex_pos += tex_data->step;
			color = get_pixel_color(tex_data->texture, tex_x, tex_y);
		}
		else
		{
			tex_x = calculate_texture_x(mlx, ray);
			tex_y = calculate_texture_y(mlx, ray, y);
			color = get_texture_pixel(mlx, ray, tex_x, tex_y);
		}
		if (ray->side == 1 && !tex_data->is_door && !tex_data->is_exit_door)
			color = (color >> 1) & 8355711;
		put_pixel_to_img(mlx, x, y, color);
	}
}

void	cast_ray(t_mlx *mlx, int x)
{
	t_render_ray	ray;
	t_texture_data	tex_data;

	init_render_ray(mlx, &ray, x);
	execute_render_dda(mlx, &ray);
	calculate_wall_dimensions(mlx, &ray);
	choose_texture(mlx, &ray, &tex_data);
	calculate_texture_position(mlx, &ray, &tex_data);
	draw_ceiling(mlx, &ray, x);
	draw_textured_wall(mlx, &ray, &tex_data, x);
	draw_floor(mlx, &ray, x);
}
