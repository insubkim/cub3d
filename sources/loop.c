/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:18:56 by inskim            #+#    #+#             */
/*   Updated: 2023/07/19 21:49:00 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/mlx/mlx.h"
#include "../headers/my_types.h"
#include "../headers/raycasting.h"

#include <stdio.h>
/* __test_player_print
 * : player 위치, 방향 벡터, 카메라 벡터 출력
 *
 * parameter - game_info: 게임 정보
 * return: none
 */
void	__test_player_print(t_game *game_info){
	printf("loc\t%lf    %lf\n", game_info->player.loc.x, game_info->player.loc.y);
	printf("dir\t%lf    %lf\n", game_info->player.dir.x, -game_info->player.dir.y);
	printf("plane\t%lf    %lf\n\n", game_info->player.plane.x, -game_info->player.plane.y);	
}

/* __test_init
 * : game_info 초기화
 *
 * parameter - game_info: 게임 정보 
 * return: none
 */
void	__test_init(t_game *game_info){
	//init map
	int width = 15;
	int height = 15;
	static char arrs[15][15] ={
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//0
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//1
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//2
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//3
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//4
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//5
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//6
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//7 x = 13, y = 7
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//8
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	// static char arrs[14][29] ={
	// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	// 	{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1},
	// 	{1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1},
	// 	{1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,0,0,1,0,0,0,1},
	// 	{1,1,0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,0,0,0,0,0,0,1},
	// 	{1,1,0,0,0,0,0,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,0,0,1},
	// 	{1,1,1,1,0,1,1,1,' ',1,1,1,0,1,0,1,' ',1,0,1,1,1,1,0,0,0,0,0,1},
	// 	{1,1,1,1,1,1,1,1,' ',1,1,1,1,1,1,1,' ',1,1,1,1,1,1,1,1,1,1,1,1}
	// };
	char **board = malloc(sizeof(char *) * height);
	for (int i = 0; i < height; i++){
		board[i] = arrs[i];
	}
	game_info->map.board = board;
	game_info->map.height = height;
	game_info->map.width = width;
	//init player
	game_info->player.loc.x = 3;
	game_info->player.loc.y = 3;
	game_info->player.dir.x = -1;
	game_info->player.dir.y = 0;
	game_info->player.plane.x = 0;
	game_info->player.plane.y = 0.66;
}

/* __test_raycasting
 * : do_raycasting 결과 값 출력
 *
 * parameter - game_info: 게임 정보 
 * return: none
 */
void	__test_raycasting(t_game *game_info){
	double arr[WIN_WIDTH] = {0,};
	for (int i = 0; i < WIN_WIDTH; i++)
		arr[i] = 0;
	double *dist_of_rays = arr;
	do_raycasting(&dist_of_rays, game_info->player, WIN_WIDTH, game_info->map.board);	
}

/* destroy_game
 * : 리소스 해제
 *
 * parameter - game_info: 게임 정보
 * return: none
 */
void	destroy_game(t_game *game_info){
	//리소스 해제.
	game_info++;
}

/* handle_close
 * : ESC, redcross 입력 시 호출되는 함수
 *
 * parameter - game_info: 게임 정보 
 * return: int
 */
int	handle_close(t_game *game_info){
	destroy_game(game_info);
	exit(0);
}

/* move_dir
 * : <- , -> 화살표 좌우를 눌렸을시 플레이어 방향 벡터와 카메라 벡터 방향 전환.  
 *	라디안 = 각도 * 원주율 / 180 임.(공식)
 *	각각의 벡터에 회전 벡터 곱해주면 방향 전환 된 후 벡터를 구할 수 있음.
 *
 * parameter - dir: 누른 화살표
 * 			 - player: 플레이어 방향 벡터와, 카메라 벡터
 * return: none
 */
void	move_dir(enum e_direction dir, t_player *player){
    double	oldDirX;
    double	oldPlaneX;
	double	rot_rate;
	
	if (dir == LEFT)
		rot_rate = ROTATE_DEGREE * PI / 180;
	else
		rot_rate = -ROTATE_DEGREE * PI / 180;
	oldDirX = player->dir.x;
	player->dir.x = player->dir.x * cos(rot_rate) - player->dir.y * sin(rot_rate);
    player->dir.y = oldDirX * sin(rot_rate) + player->dir.y * cos(rot_rate);
	oldPlaneX = player->plane.x;
	player->plane.x = player->plane.x * cos(rot_rate) - player->plane.y * sin(rot_rate);
	player->plane.y = oldPlaneX * sin(rot_rate) + player->plane.y * cos(rot_rate);
}

/* move_player
 * : WASD를 눌렸을시 플레이어 위치를 방향벡터에 따라 이동시킴.
 *	atan2(기울기) -> 라디안임.
 *	라디안을 알면 sin cos를 이용하여 x,y 구할 수 있음.
 *	up down 은 방향 벡터로, left right은 카메라 벡터를 이용함(방향벡터와 수직이므로).
 * 	down, left의 경우 반대로 가야하니 음의 방향으로 이동함.
 * 
 * parameter - dir: WASD 키 
 * 			 - game_info: 게임 정보
 * return: none
 */
void	move_player(enum e_direction dir, t_game *game_info){
	double	radian;
	double	x;
	double	y;

	if (dir == UP || dir == DOWN)//dir 방향일때,
		radian = atan2(-game_info->player.dir.y, game_info->player.dir.x);
	else //plane 방향일때,
		radian = atan2(-game_info->player.plane.y, game_info->player.plane.x);
	x = cos(radian) * ((double)1 / TILESIZE);
	y = sin(radian) * ((double)1 / TILESIZE);
	if (dir == DOWN || dir == LEFT)// down 이나 left면  방향 반대이므로 -1 곱함.
	{
		x *= -1;
		y *= -1;
	}
	x += game_info->player.loc.x;
	y += game_info->player.loc.y;

	if (game_info->map.board[(int)y][(int)x] != 1)
	{
		game_info->player.loc.x = x;
		game_info->player.loc.y = y;
	}
}

//테스트용
void    make_img(t_game *game_info);
void    draw_map(t_player player, t_img img, t_map map);
void    draw_floor_ceil(t_game *game_info, int floor_color, int ceil_color);


/* handle_key
 * : mlx에 등록되어 mlx_loop 도중 키보드 입력시 대응되는 키보드 값을 처리함.
 *   플레이어 이동 혹은 시선 이동임. 변경이 되면 새로운 화면 출력
 *
 * parameter - keycode: 입력 받은 키보드 값
 * 			 - game_info: 게임 정보
 * return: int (왜 인지는 모르겠음.)
 */
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
	else
		return (0);
	//천장, 바닥 표시 + raycasting + map 화면에 표시, 이전 이미지 파괴.
	//__test_raycasting(game_info);
	//__test_player_print(game_info);
	make_img(game_info);
	draw_floor_ceil(game_info, 0x00000000, 0x00FF0000);
	draw_map(game_info->player, game_info->img, game_info->map);
	mlx_put_image_to_window(game_info->mlx, game_info->win, game_info->img.img, 0, 0);
	return (0);
}

int	main(void){
	t_game	game_info;
	game_info.mlx = mlx_init();
	game_info.win = mlx_new_window(game_info.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	
	__test_init(&game_info);
	//parse + set t_game

	//천장 바닥 표시 + raycasting + map표시 첫 화면 표시 
	make_img(&game_info);
	draw_floor_ceil(&game_info, 0x00000000, 0x00FF0000);
	draw_map(game_info.player, game_info.img, game_info.map);
	mlx_put_image_to_window(game_info.mlx, game_info.win, game_info.img.img, 0, 0);
	//__test_raycasting(&game_info);
	//__test_player_print(&game_info);
	
	//hook
	mlx_hook(game_info.win, 2, 0, handle_key, &game_info);
	mlx_hook(game_info.win, 17, 0, handle_close, &game_info);
	mlx_loop(game_info.mlx);
	//리소스 해제
	destroy_game(&game_info);
	return (0);
}