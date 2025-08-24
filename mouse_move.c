/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izahr <izahr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:24:04 by izahr             #+#    #+#             */
/*   Updated: 2025/08/24 02:40:13 by izahr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

static void	rotate_vector(float *x, float *y, float angle)
{
	float	last_x;
	float	cos_angle;
	float	sin_angle;

	last_x = *x;
	cos_angle = cosf(angle);
	sin_angle = sinf(angle);
	*x = last_x * cos_angle - *y * sin_angle;
	*y = last_x * sin_angle + *y * cos_angle;
}

static float	normalize_angle(float angle)
{
	angle = fmodf(angle, 2.0f * M_PI);
	if (angle < 0)
		angle += 2.0f * M_PI;
	return (angle);
}

static int	first_init(int *flag, int x, int *last_x)
{
	*last_x = x;
	*flag = 1;
	return (0);
}

static int	mouse_move(int x, int y, t_mlx *mlx)
{
	static int	last_x;
	static int	flag;
	static int	accumulated_delta;
	float		delta_x;
	float		rotation_angle;

	(void)y;
	if (flag == 0)
		return (first_init(&flag, x, &last_x));
	delta_x = (float)(x - last_x);
	last_x = mlx->win_width / 2;
	accumulated_delta += (int)delta_x;
	if (abs(accumulated_delta) > 1)
	{
		rotation_angle = accumulated_delta * 0.001f;
		accumulated_delta = 0;
		rotate_vector(&mlx->player.dir_x, &mlx->player.dir_y, rotation_angle);
		rotate_vector(&mlx->player.plane_x, &mlx->player.plane_y,
			rotation_angle);
		mlx->player.angle = normalize_angle(mlx->player.angle + rotation_angle);
		mlx_mouse_move(mlx->mlx_ptr, mlx->win_ptr, mlx->win_width / 2,
			mlx->win_height / 2);
	}
	return (0);
}

int	setup_hooks_and_start(t_mlx *mlx)
{
	render_3d_view(mlx);
	mlx_hook(mlx->win_ptr, 2, 1L << 0, key_press, mlx);
	mlx_hook(mlx->win_ptr, 3, 1L << 1, key_release, mlx);
	mlx_hook(mlx->win_ptr, 6, 1L << 6, mouse_move, mlx);
	mlx_mouse_move(mlx->mlx_ptr, mlx->win_ptr, mlx->win_width / 2,
		mlx->win_height / 2);
	mlx_hook(mlx->win_ptr, 17, 0, exit_program, mlx);
	mlx_loop_hook(mlx->mlx_ptr, game_loop, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
