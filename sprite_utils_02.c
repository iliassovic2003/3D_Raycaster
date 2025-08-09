#include "Cub3D.h"

static void	init_sprite_render(t_mlx *mlx, t_sprite_data *data,
		t_sprite_render *render, int i)
{
	float	inv_det;

	render->render_x = data->sprites[i]->x + data->float_offset;
	render->render_y = data->sprites[i]->y;
	render->sprite_x = render->render_x - mlx->player.p_x;
	render->sprite_y = render->render_y - mlx->player.p_y;
	inv_det = 1.0 / (mlx->player.plane_x * mlx->player.dir_y - mlx->player.dir_x
			* mlx->player.plane_y);
	render->transform_x = inv_det * (mlx->player.dir_y * render->sprite_x
			- mlx->player.dir_x * render->sprite_y);
	render->transform_y = inv_det * (-mlx->player.plane_y * render->sprite_x
			+ mlx->player.plane_x * render->sprite_y);
	render->sprite_screen_x = (int)((mlx->win_width / 2) * (1
				+ render->transform_x / render->transform_y));
	render->sprite_height = abs((int)(mlx->win_height / render->transform_y));
	render->sprite_width = render->sprite_height;
}

static void	calculate_sprite_boundaries(t_mlx *mlx, t_sprite_render *render)
{
	render->draw_start_y = -render->sprite_height / 2 + mlx->win_height / 2;
	if (render->draw_start_y < 0)
		render->draw_start_y = 0;
	render->draw_end_y = render->sprite_height / 2 + mlx->win_height / 2;
	if (render->draw_end_y >= mlx->win_height)
		render->draw_end_y = mlx->win_height - 1;
	render->draw_start_x = -render->sprite_width / 2 + render->sprite_screen_x;
	if (render->draw_start_x < 0)
		render->draw_start_x = 0;
	render->draw_end_x = render->sprite_width / 2 + render->sprite_screen_x;
	if (render->draw_end_x >= mlx->win_width)
		render->draw_end_x = mlx->win_width - 1;
}

static void	draw_sprite_stripe(t_mlx *mlx, t_sprite_render *render,
		t_sprite *sprite, int stripe)
{
	int				y;
	int				tex_x;
	int				tex_y;
	int				d;
	unsigned int	color;

	tex_x = (int)(256 * (stripe - (-render->sprite_width / 2
					+ render->sprite_screen_x)) * sprite->texture.width
			/ render->sprite_width) / 256;
	y = render->draw_start_y;
	while (y < render->draw_end_y)
	{
		d = y * 256 - mlx->win_height * 128 + render->sprite_height * 128;
		tex_y = ((d * sprite->texture.height) / render->sprite_height) / 256;
		color = get_pixel_color(&sprite->texture, tex_x, tex_y);
		if ((color & 0x00FFFFFF) != 0)
			put_pixel_to_img(mlx, stripe, y, color);
		y++;
	}
}

static void	draw_sprite(t_mlx *mlx, t_sprite_data *data,
		t_sprite_render *render, int i)
{
	int	stripe;

	stripe = render->draw_start_x;
	while (stripe < render->draw_end_x)
	{
		if (stripe >= 0 && stripe < mlx->win_width && render->transform_y > 0
			&& render->transform_y < data->zbuffer[stripe])
			draw_sprite_stripe(mlx, render, data->sprites[i], stripe);
		stripe++;
	}
}

void	render_sprites(t_mlx *mlx)
{
	t_sprite_data	data;
	t_sprite_render	render;
	float			zbuffer[mlx->win_width];
	int				i;

	data.zbuffer = zbuffer;
	initialize_sprite_data(mlx, &data);
	sort_sprites(&data);
	calculate_zbuffer(mlx, zbuffer);
	i = 0;
	while (i < data.sprite_count)
	{
		init_sprite_render(mlx, &data, &render, i);
		calculate_sprite_boundaries(mlx, &render);
		draw_sprite(mlx, &data, &render, i);
		i++;
	}
}
