#ifndef CUB3D_H
#define CUB3D_H

#include "mlx/mlx.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <fcntl.h>
#include <stdbool.h>
#include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_player
{
    float       p_x;
    float       p_y;
    float       angle;
    float       spawn_angle;
    float       dir_x;
    float       dir_y;
    float       plane_x;
    float       plane_y;
    bool        has_green_keycard;
    bool        has_white_keycard;
    bool        is_holding_keycard;
    int         spawn_x;
    int         spawn_y;
    int         holding_keycard_type;
}               t_player;

typedef struct  s_color
{
    int R;
    int G;
    int B;
}               t_color;

typedef struct  s_img
{
    void        *img_ptr;
    char        *img_data;
    int         width;
    int         height;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_img;

typedef struct s_door
{
    float       door_x;
    float       door_y;
    float       open_state;
    bool        is_opening;
    bool        is_closing;
    bool        is_locked;
    int         key_type;
    t_img       texture;
}               t_door;

typedef struct s_sprite
{
    float   x;
    float   y;
    float   distance;
    bool    visible;
    t_img   texture;
}               t_sprite;

typedef struct s_map
{
    int width;
    int height;
    char **map2D;
}               t_map;

typedef struct s_keys
{
    int         w;
    int         a;
    int         s;
    int         d;
    int         left;
    int         right;
}               t_keys;

typedef struct s_mlx
{
    void        *mlx_ptr;
    void        *win_ptr;
    t_player    player;
    bool        show_map;
    t_img       img;
    t_img       textures[4]; //NO, SO, WE, EA
    t_sprite    green_keycard;
    t_sprite    white_keycard;
    t_color     floor;
    t_color     ceiling;
    t_map       map;
    t_door      door;
    t_door      exit_door;
    int         win_height;
    int         win_width;
    float       animation_timer;
    t_keys      keys;
}               t_mlx;

typedef struct s_tmp1
{
    int x;
    int y;
    int size;
    int color;
}               t_tmp1;

typedef struct s_mini_data
{
	int	tile_size;
	int	actual_width;
	int	actual_height;
}	t_mini_data;

typedef struct s_tmp2
{
    int		x;
	int		y;
	int		i;
	int		j;
    float	fx;
	float	fy;
	float	fi;
	float	fj;
}               t_tmp2;

typedef struct s_ray_data
{
	float	camera_x;
	float	ray_dir_x;
	float	ray_dir_y;
	int		map_x;
	int		map_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_ray_data;

typedef struct s_sprite_data
{
	t_sprite	*sprites[2];
	float		sprite_distances[2];
	int			sprite_count;
	float		*zbuffer;
	float		float_offset;
}	t_sprite_data;

typedef struct s_sprite_render
{
	float	render_x;
	float	render_y;
	float	sprite_x;
	float	sprite_y;
	float	transform_x;
	float	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_x;
	int		draw_end_x;
	int		draw_start_y;
	int		draw_end_y;
}	t_sprite_render;

typedef struct  s_tmp3
{
    float	    door_dist_x;
	float	    door_dist_y;
	float	    door_dist;
	float	    exit_dist_x;
	float	    exit_dist_y;
	float	    exit_dist;
}               t_tmp3;

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_M 109
# define KEY_F 102
# define KEY_TAB 65289
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_render_ray
{
	float	camera_x;
	float	ray_dir_x;
	float	ray_dir_y;
	int		map_x;
	int		map_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	float	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_render_ray;

typedef struct s_texture_data
{
	t_img	*texture;
	float	wall_x;
	int		tex_x;
	float	step;
	float	tex_pos;
	int		is_door;
	int		is_exit_door;
}	        t_texture_data;

typedef struct s_move
{
	float	dx;
	float	dy;
	float	new_x;
	float	new_y;
	int		can_move_x;
	int		can_move_y;
	int		map_x;
	int		map_y;
}	t_move;


char			**ft_split(char const *s, char c);
char			*get_next_line(int fd, int k);
char			*ft_strchr(char *s, int c);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strdup(char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
char            *ft_strtrim(char *s);
char			*ft_strstr(const char *haystack, const char *needle);
void            ft_bzero(void *s, size_t n);
size_t			ft_strlen(char *str);
int	            ft_atoi(const char *str);
void	        free_arr(char **arr);
int             init_map(t_mlx *mlx);
void            fill_map(char *line, t_mlx *mlx, int k, int *flag);
void            print2Dmap(t_mlx mlx);
int             check_map(t_mlx mlx);
int             load_textures(char *line, t_mlx *mlx);
int             parse_color(char *line, t_mlx *mlx);
int             ft_strcmp(char *s1, char *s2);
void            free_map(t_mlx *mlx);
void            free_res(int fd, t_mlx *mlx, char *line);
void            put_pixel_to_img(t_mlx *mlx, int x, int y, int color);
void            draw_filled_circle(t_mlx *mlx, int cr_x, int c_y, int rad);
void            draw_hollow_square(t_mlx *mlx, t_tmp1 tmp);
void            draw_held_keycard(t_mlx *mlx);
void            draw_minimap_keycards(t_mlx *mlx, t_mini_data *data);
void            draw_minimap_player(t_mlx *mlx, t_mini_data *data);
void            draw_minimap(t_mlx *mlx, int width, int height);
void            calculate_zbuffer(t_mlx *mlx, float *zbuffer);
unsigned int 	get_pixel_color(t_img *texture, int x, int y);
void			initialize_sprite_data(t_mlx *mlx, t_sprite_data *data);
void			sort_sprites(t_sprite_data *data);
void			render_sprites(t_mlx *mlx);
void			initialize_sprite_data(t_mlx *mlx, t_sprite_data *data);
void			sort_sprites(t_sprite_data *data);
void			init_render_ray(t_mlx *mlx, t_render_ray *ray, int x);
void			execute_render_dda(t_mlx *mlx, t_render_ray *ray);
void			cast_ray(t_mlx *mlx, int x);
void			calculate_wall_dimensions(t_mlx *mlx, t_render_ray *ray);
void			render_3d_view(t_mlx *mlx);
int 			exit_program(t_mlx *mlx);
int				handle_doors(t_mlx *mlx);
void			move_player(t_mlx *mlx, t_move *move, float buffer);
void			rotate_player(t_mlx *mlx, float rot_step, int direction);
int				key_press(int keycode, t_mlx *mlx);
int				key_release(int keycode, t_mlx *mlx);
void			handle_movement(t_mlx *mlx);
int 			load_keycard_textures(t_mlx *mlx);
int				setup_player_and_window(t_mlx *mlx);
int 			load_keycard_textures(t_mlx *mlx);
int 			game_loop(t_mlx *mlx);
int				read_map_dimensions(t_mlx *mlx, char *filename, int offset);
int				fill_map_data(t_mlx *mlx, int fd, int offset);
int    			opening_file(t_mlx *mlx, char *path);
void 			first_pass(char **argv, t_mlx *mlx, int *offset);
void 			draw_floor(t_mlx *mlx, t_render_ray *ray, int x);
void 			draw_ceiling(t_mlx *mlx, t_render_ray *ray, int x);
int				calculate_texture_x(t_mlx *mlx, t_render_ray *ray);
int				calculate_texture_y(t_mlx *mlx, t_render_ray *ray, int y);
int				setup_hooks_and_start(t_mlx *mlx);
int				get_texture_pixel(t_mlx *mlx, t_render_ray *ray, int tex_x, int tex_y);

#endif