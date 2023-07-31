/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:37:39 by insub             #+#    #+#             */
/*   Updated: 2023/07/28 21:24:38 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/mlx/mlx.h"
#include "../library/libft/libft.h"
#include "../headers/my_types.h"
#include "../headers/drawing_3d.h"
#include <stdio.h>

void    make_img(t_game *game_info);
void    draw_map(t_player player, t_img img, t_map map);
void    draw_floor_ceil(t_game *game_info, int floor_color, int ceil_color);
void    print_img(t_game *game_info);

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
	int width = 33;
	int height = 14;
	// static char arrs[15][15] = {"111111111111111",
	// 							"100000000000001",
	// 							"100000000000001",
	// 							"100000000000001",
	// 							"100000000000001",
	// 							"100000000000001",
	// 							"100000000000001",
	// 							"100000000000001",
	// 							"100000000000001",
	// 							"100000000000001",
	// 							"100000000000001",
	// 							"100000000000001",
	// 							"100000000000001",
	// 							"100000000000001",
	// 							"111111111111111"};
								
	// static char arrs[14][29] ={
	// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	// 	{1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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

	static char arrs[14][33] ={"111111111111111111111111111111111",
							   "100000000000000000110000000000001",
							   "100000000000000001110000000000001",
							   "100000000000000000000000000000001",
							   "111111111111110001110000000000001",
							   "100000000011000001110111110011111",
							   "11110111111111011100000010001    ",
							   "11110111111111000001010010001    ",
							   "11000000110101011100000000001    ",
							   "10000000000000001100000010001    ",
							   "10000000000000001101010010001    ",
							   "11000001110101011111011010001    ",
							   "11110111 1110101 100011000001    ",
							   "11111111 1111111 111111111111    "};
	//static char arrs[3][3] = {"111","101", "111"}; 
	char **board = malloc(sizeof(char *) * height);
	for (int i = 0; i < height; i++){
		board[i] = ft_strdup(arrs[i]);
	}
	game_info->map.board = board;
	game_info->map.height = height;
	game_info->map.width = width;
	//init player
	game_info->player.loc.x = 7;// + (double)1 / TILESIZE;
	game_info->player.loc.y = 2;// + (double)1 / TILESIZE;
	game_info->player.dir.x = 0;
	game_info->player.dir.y = 1;
	game_info->player.plane.x = 0.66;
	game_info->player.plane.y = 0;
}

/* __test_raycasting
 * : do_raycasting 결과 값 출력
 *
 * parameter - game_info: 게임 정보 
 * return: none
 */
// void	__test_raycasting(t_game *game_info){
// 	double arr[WIN_WIDTH] = {0,};
// 	for (int i = 0; i < WIN_WIDTH; i++)
// 		arr[i] = 0;
// 	double *dist_of_rays = arr;
// 	do_raycasting(&dist_of_rays, game_info->player, WIN_WIDTH, game_info->map.board);	
// }