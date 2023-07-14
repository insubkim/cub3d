/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:18:56 by inskim            #+#    #+#             */
/*   Updated: 2023/07/14 18:22:28 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/mlx"

void	destroy_game(t_game *game_info){
	//리소스 해제.
	game_info++;
}

int	handle_close(t_game *game_info){
	destroy_game(game_info);
	exit(0);
}

void	move_dir(enum e_direction dir, t_player *player){
    double	oldDirX;
    double	oldPlaneX;
	double	rot_rate;
	
	if (dir == LEFT)
		rot_rate = -1 * 3.1415926535 / 180;
	else
		rot_rate = 1 * 3.1415926535 / 180;
	oldDirX = player->dir.x;
	player->dir.x = player->dir.x * cos(rot_rate) - player->dir.y * sin(rot_rate);
    player->dir.y = oldDirX * sin(rot_rate) + player->dir.y * cos(rot_rate);
    oldPlaneX = player->plane.x;
	player->plane.x = player->plane.x * cos(rot_rate) - player->plane.y * sin(rot_rate);
    player->plane.y = oldPlaneX * sin(rot_rate) + player->plane.y * cos(rot_rate);
}

void	move_player(enum e_direction dir, t_game *game_info){
	double	x;
	double	y;
	double	offset;

	x = game_info->player.loc.x;
	y = game_info->player.loc.y;
	offset = (double)1 / TILESIZE;
	if (dir == UP)
		x += offset;
	else if (dir == DOWN)
		x -= offset;
	else if (dir == LEFT)
		y -= offset;
	else if (dir == RIGHT)
		y += offset;
	if (x > 1 && x < game_info->map.width - 1 && y > 1 && y < game_info->map.height - 1)
	{
		game_info->player.loc.x = x;
		game_info->player.loc.y = y;	
	}
}

int	handle_key(int keycode, t_game *game_info){
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
	//raycasting + 화면에 표시
	return (0);
}

int	main(void){
	t_game	game_info;
	//parse + init t_game

	//raycasting + 화면에 표시

	//hook
	//어떤 키 입력이 들어오면 플레이어 위치를 변경시키고 화면에 표시.
	mlx_hook(game_info.win, 2, 0, handle_key, &game_info);
	//리소스 해제
	mlx_hook(game_info.win, 17, 0, handle_close, &game_info);
	mlx_loop(game_info.mlx);
	//리소스 해제
	destroy_game(game_info);
	return (0);
}