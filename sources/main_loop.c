/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:18:56 by inskim            #+#    #+#             */
/*   Updated: 2023/07/31 15:55:23 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/my_types.h"
// #include "../headers/drawing_3d.h"
#include "../library/mlx/mlx.h"

//test 용
// void    make_img(t_game *game_info);
// void    draw_map(t_player player, t_img img, t_map map);
// void    draw_floor_ceil(t_game *game_info, int floor_color, int ceil_color);
// void    print_img(t_game *game_info);
// void	__test_init(t_game *game_info);

int		init(char *file_name, t_game *game_info);
int		print_error(int error);
void	move_player(enum e_direction dir, t_game *game_info);
void	move_dir(enum e_direction dir, t_player *player);

void	destroy_game(t_game *game_info)
{
	// TODO: 리소스 해제.
	game_info++;
}

int	handle_close(t_game *game_info)
{
	destroy_game(game_info);
	exit(0);
}

int	handle_key(int keycode, t_game *game_info)
{
	if (keycode == KEY_LEFT)
		move_dir(LEFT, &game_info->player);
	else if (keycode == KEY_RIGHT)
		move_dir(RIGHT, &game_info->player);
	else if (keycode == KEY_W)
		move_player(UP, game_info);
	else if (keycode == KEY_S)
		move_player(DOWN, game_info);
	else if (keycode == KEY_A)
		move_player(LEFT, game_info);
	else if (keycode == KEY_D)
		move_player(RIGHT, game_info);
	else if (keycode == KEY_ESC)
		handle_close(game_info);
	else
		return (0);
	print_img(game_info);
	return (0);
}

int	handle_mouse(t_game *game_info)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game_info->win, &x, &y);
	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
		return (0);
	if (x < WIN_WIDTH / 2 - (WIN_WIDTH / 5))
		handle_key(KEY_LEFT, game_info);
	else if (x > WIN_WIDTH / 2 + (WIN_WIDTH / 5))
		handle_key(KEY_RIGHT, game_info);
	else
		print_img(game_info);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game_info;

	if (argc != 2)
		return (print_error(ERROR_ARG_NUM));
	if (init(argv[1], &game_info) == ERROR_INT)
		return (1);
	print_img(&game_info);
	mlx_hook(game_info.win, ON_KEYDOWN, 0, handle_key, &game_info);
	mlx_hook(game_info.win, ON_DESTROY, 0, handle_close, &game_info);
	mlx_mouse_hide();
	mlx_loop_hook(game_info.mlx, handle_mouse, &game_info);
	mlx_loop(game_info.mlx);
	destroy_game(&game_info);
	return (0);
}
