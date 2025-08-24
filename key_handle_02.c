#include "Cub3D.h"

static t_move handle_translation_movement(t_mlx *mlx, float move_speed)
{
    t_move move;
    
    move.dx = 0;
    move.dy = 0;
    if (mlx->keys.w)
    {
        move.dx += mlx->player.dir_x * move_speed;
        move.dy += mlx->player.dir_y * move_speed;
    }
    if (mlx->keys.s)
    {
        move.dx -= mlx->player.dir_x * move_speed;
        move.dy -= mlx->player.dir_y * move_speed;
    }
    if (mlx->keys.d)
    {
        move.dx += mlx->player.plane_x * move_speed;
        move.dy += mlx->player.plane_y * move_speed;
    }
    if (mlx->keys.a)
    {
        move.dx -= mlx->player.plane_x * move_speed;
        move.dy -= mlx->player.plane_y * move_speed;
    }
    return (move);
}

void handle_movement(t_mlx *mlx)
{
    float move_speed;
    float rot_speed;
    t_move move;
    
    move_speed = 0.015f;
    rot_speed = 0.015f;
    move = handle_translation_movement(mlx, move_speed);
    if (move.dx != 0 || move.dy != 0)
        move_player(mlx, &move, 0.1f);
    if (mlx->keys.right)
        rotate_player(mlx, rot_speed, 1);
    if (mlx->keys.left)
        rotate_player(mlx, rot_speed, 0);
}

int key_release(int keycode, t_mlx *mlx)
{
    if (keycode == KEY_W)
        mlx->keys.w = 0;
    else if (keycode == KEY_A)
        mlx->keys.a = 0;
    else if (keycode == KEY_S)
        mlx->keys.s = 0;
    else if (keycode == KEY_D)
        mlx->keys.d = 0;
    else if (keycode == KEY_LEFT)
        mlx->keys.left = 0;
    else if (keycode == KEY_RIGHT)
        mlx->keys.right = 0;
    return (0);
}
