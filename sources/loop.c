/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:18:56 by inskim            #+#    #+#             */
/*   Updated: 2023/07/16 00:09:11 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/mlx/mlx.h"
#include "../headers/my_types.h"

void	destroy_game(t_game *game_info){
	//리소스 해제.
	game_info++;
}

int	handle_close(t_game *game_info){
	destroy_game(game_info);
	exit(0);
}

/*
	라디안 = 각도 * 원주율 / 180 임.(공식)
	회전 벡처 곱해주면 쉽게 회전 후 벡터 구할 수 있음.
*/
void	move_dir(enum e_direction dir, t_player *player){
    double	oldDirX;
    double	oldPlaneX;
	double	rot_rate;
	
	if (dir == LEFT)
		rot_rate = -ROTATE_DEGREE * PI / 180;
	else
		rot_rate = ROTATE_DEGREE * PI / 180;
	oldDirX = player->dir.x;
	player->dir.x = player->dir.x * cos(rot_rate) - player->dir.y * sin(rot_rate);
    player->dir.y = oldDirX * sin(rot_rate) + player->dir.y * cos(rot_rate);
    oldPlaneX = player->plane.x;
	player->plane.x = player->plane.x * cos(rot_rate) - player->plane.y * sin(rot_rate);
    player->plane.y = oldPlaneX * sin(rot_rate) + player->plane.y * cos(rot_rate);
}

/*
	atan(기울기) -> 라디안임.
	라디안을 알면 sin cos를 이용하여 x,y 구할 수 있음.
	up down 은 방향 벡터로, left right은 카메라 벡터로(방향벡터와 수직이므로)
	down, left의 경우 반대로 가야하니 음수처리.
*/
void	move_player(enum e_direction dir, t_game *game_info){
	double	radian;
	double	x;
	double	y;

	if (dir == UP || dir == DOWN)//dir 방향으로 
		radian = atan(game_info->player.dir.y / game_info->player.dir.x);
	else //if (dir == LEFT || dir == RIGHT)//plane 방향으로 
		radian = atan(game_info->player.plane.y / game_info->player.plane.x);
	x = cos(radian) * ((double)1 / TILESIZE);
	y = sin(radian) * ((double)1 / TILESIZE);
	if (dir == DOWN || dir == LEFT)
	{
		x *= -1;
		y *= -1;
	}
	x += game_info->player.loc.x;
	y += game_info->player.loc.y;
	if (x > 1 && x < game_info->map.width - 1 &&\
		 y > 1 && y < game_info->map.height - 1)//범위 체크
	{
		game_info->player.loc.x = x;
		game_info->player.loc.y = y;
	}
}

#include <stdio.h>//printf용. 지워야함.
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
	//---------test
	printf("loc\t%lf    %lf\n", game_info->player.loc.x, game_info->player.loc.y);
	printf("dir\t%lf    %lf\n", game_info->player.dir.x, game_info->player.dir.y);
	printf("plane\t%lf    %lf\n\n", game_info->player.plane.x, game_info->player.plane.y);	
	//-------------
	
	//raycasting + 변경 된 화면에 표시, 이전 이미지 파괴.
	return (0);
}

int	main(void){
	t_game	game_info;
	game_info.mlx = mlx_init();
	game_info.win = mlx_new_window(game_info.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	
	
	//-------test
	game_info.map.height = 20;
	game_info.map.width = 20;
	game_info.player.loc.x = 10;
	game_info.player.loc.y = 10;
	game_info.player.dir.x = -1;
	game_info.player.dir.y = 0;
	game_info.player.plane.x = 0;
	game_info.player.plane.y = 0.66;
	//-----------

	//parse + init t_game

	//raycasting + 첫 화면에 표시

	//hook
	//어떤 키 입력이 들어오면 플레이어 위치를 변경시키고 화면에 표시.
	mlx_hook(game_info.win, 2, 0, handle_key, &game_info);
	//리소스 해제
	mlx_hook(game_info.win, 17, 0, handle_close, &game_info);
	mlx_loop(game_info.mlx);
	//리소스 해제
	destroy_game(&game_info);
	return (0);
}