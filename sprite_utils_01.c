#include "Cub3D.h"

static void	init_ray_casting_v2(t_mlx *mlx, t_ray_data *ray)
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

static void	init_ray_casting(t_mlx *mlx, int x, t_ray_data *ray)
{
	ray->camera_x = 2 * x / (float)mlx->win_width - 1;
	ray->ray_dir_x = mlx->player.dir_x + mlx->player.plane_x * ray->camera_x;
	ray->ray_dir_y = mlx->player.dir_y + mlx->player.plane_y * ray->camera_x;
	ray->map_x = (int)mlx->player.p_x;
	ray->map_y = (int)mlx->player.p_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	init_ray_casting_v2(mlx, ray);
}

static void	perform_dda(t_mlx *mlx, t_ray_data *ray)
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

void	calculate_zbuffer(t_mlx *mlx, float *zbuffer)
{
	int x;
	t_ray_data ray;
	float perp_wall_dist;

	x = 0;
	while (x < mlx->win_width)
	{
		init_ray_casting(mlx, x, &ray);
		perform_dda(mlx, &ray);
		if (ray.side == 0)
			perp_wall_dist = (ray.side_dist_x - ray.delta_dist_x);
		else
			perp_wall_dist = (ray.side_dist_y - ray.delta_dist_y);
		zbuffer[x] = perp_wall_dist;
		x++;
	}
}
