#include "Cub3D.h"

static void	init_render_rayv2(t_mlx *mlx, t_render_ray *ray)
{
	ray->hit = 0;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (mlx->player.p_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - mlx->player.p_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (mlx->player.p_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - mlx->player.p_y)
			* ray->delta_dist_y;
	}
}

void	init_render_ray(t_mlx *mlx, t_render_ray *ray, int x)
{
	ray->camera_x = 2 * x / (float)mlx->win_width - 1;
	ray->ray_dir_x = mlx->player.dir_x + mlx->player.plane_x * ray->camera_x;
	ray->ray_dir_y = mlx->player.dir_y + mlx->player.plane_y * ray->camera_x;
	ray->map_x = (int)mlx->player.p_x;
	ray->map_y = (int)mlx->player.p_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1000000000;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1000000000;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	init_render_rayv2(mlx, ray);
}

void	execute_render_dda(t_mlx *mlx, t_render_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= mlx->map.width || ray->map_y < 0
			|| ray->map_y >= mlx->map.height)
			break ;
		if (mlx->map.map2D[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	render_walls(t_mlx *mlx)
{
	int	x;

	x = 0;
	while (x < mlx->win_width)
	{
		cast_ray(mlx, x);
		x++;
	}
}

void	render_3d_view(t_mlx *mlx)
{
	int	minimap_width;
	int	minimap_height;

	render_walls(mlx);
	render_sprites(mlx);
	if (mlx->show_map)
	{
		minimap_width = mlx->win_width / 4;
		minimap_height = mlx->win_height / 4;
		draw_minimap(mlx, minimap_width, minimap_height);
	}
	draw_held_keycard(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
}
