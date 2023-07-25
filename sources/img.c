/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:25:23 by insub             #+#    #+#             */
/*   Updated: 2023/07/25 16:27:26 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/mlx/mlx.h"
#include "../headers/my_types.h"
#include "../library/libft/libft.h"


void    draw_map(t_player player, t_img img, t_map map);//test
void	__test_player_print(t_game *game_info);//test

/* make_img
 * : mlx 이미지 초기화, 플레이어 이동시 변경 전, 변경 후 img 둘 을 가지게 됨. 
 *   변경 후 img를 화면에 표시하고 나서 변경 전 img를 파괴시키기 때문에,
 *   변경 전 img 사본을 img_copy에 저장시킴.
 * parameters - game_info: 게임 정보
 * return: none
 */
void    make_img(t_game *game_info)
{
    game_info->img_copy = game_info->img.img;
    game_info->img.img = mlx_new_image(game_info->mlx, WIN_WIDTH, WIN_HEIGHT);   
    game_info->img.addr = mlx_get_data_addr(game_info->img.img, \
                &(game_info->img.bits_per_pixel), &(game_info->img.line_length), \
                &(game_info->img.endian));
}

/* my_mlx_pixel_put
 * : img (x, y) 좌표에 color 픽셀 값을 넣음.
 *
 * parameter - img: 픽셀 넣을 이미지
 *           - x: x좌표
 *           - y: y좌표
 *           - color: 픽셀 색
 * return: none
 */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/* draw_floor_ceil
 * : 바닥과 천장을 img에 표시함.
 * parameters - game_info: 게임 정보
 *            - floor_color: 바닥 색
 *            - ceil_color: 천장 색
 * return: none
 */
void    draw_floor_ceil(t_game *game_info, int floor_color, int ceil_color)
{
    int i;
    int j;
    int color;

    color = ceil_color;
    i = 0;
    while (i < WIN_HEIGHT)
    {
        if (i == WIN_HEIGHT / 2)
            color = floor_color;
        j = 0;
        while (j < WIN_WIDTH)
        {
            my_mlx_pixel_put(&(game_info->img), j, i, color);
            j++;
        }
        i++;
    }
}

void	do_raycasting(double **dist_of_rays, t_player player, int screen_width, char **map_board);

/* get_real_pixel_to_draw
 * : 어안효과(같은 거리에 있는 일직선의 벽이 광선의 방향으로 인해 둥글게 그려지는 현상, 볼록렌즈)를 
 *   없애기 위해 실제로 화면에 그려지는 벽의 높이를 구함
 * 
 * parameters - screen_height: 시야에 잡히는 화면의 높이
 *            - dist_of_ray: 광선의 거리
 * return: none
 */
void	get_real_pixel_to_draw(int *start, int *end, int screen_height, double dist_of_ray)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	//Calculate height of line to draw on screen
	line_height = (int)(screen_height / dist_of_ray);

	//calculate lowest and highest pixel to fill in current stripe
	draw_start = (-line_height / 2) + (screen_height / 2);
	if(draw_start < 0)
		draw_start = 0;
	draw_end = (line_height / 2) + (screen_height / 2);
	if(draw_end >= screen_height)
		draw_end = screen_height - 1;

    *start = draw_start;
    *end = draw_end;
}

void    draw_wall(t_game *game_info)
{
	double arr[WIN_WIDTH] = {0,};
	for (int i = 0; i < WIN_WIDTH; i++)
		arr[i] = 0;
	double *dist_of_rays = arr;
	do_raycasting(&dist_of_rays, game_info->player, WIN_WIDTH, game_info->map.board);

	int	draw_start;
	int	draw_end;
    
	// Calculate height of line to draw on screenW=
	for (int i = 0; i < WIN_WIDTH; i++)
	{
        get_real_pixel_to_draw(&draw_start, &draw_end, WIN_HEIGHT, dist_of_rays[i]);
        for (int j = draw_start; j <= draw_end; j++)
            my_mlx_pixel_put(&(game_info->img), i, j, 0x00008000);
    }
}

/* print_img
 * : mlx 이미지 생성 -> 천장 바닥 -> 벽 -> 맵 순으로 이미지 초기화 후, 화면에 표시
 * parameter - game_info: 게임정보
 * return: none
 */
void    print_img(t_game *game_info)
{
	make_img(game_info);
	draw_floor_ceil(game_info, 0x00000000, 0x00FF0000);
    draw_wall(game_info);
	draw_map(game_info->player, game_info->img, game_info->map);
	mlx_put_image_to_window(game_info->mlx, game_info->win, game_info->img.img, 0, 0);
	if (game_info->img_copy)
		mlx_destroy_image(game_info->mlx, game_info->img_copy);
}