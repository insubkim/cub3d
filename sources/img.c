/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:25:23 by insub             #+#    #+#             */
/*   Updated: 2023/07/20 21:04:11 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/mlx/mlx.h"
#include "../headers/my_types.h"
#include "../library/libft/libft.h"

void    make_img(t_game *game_info)
{
    game_info->img_copy = game_info->img.img;
    game_info->img.img = mlx_new_image(game_info->mlx, WIN_WIDTH, WIN_HEIGHT);   
    game_info->img.addr = mlx_get_data_addr(game_info->img.img, \
                &(game_info->img.bits_per_pixel), &(game_info->img.line_length), \
                &(game_info->img.endian));
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

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

    //220, 220  크기 맵 생성.
    //기존 img 위에 픽셀 값을 덮어씌울거임.
    //img 좌표는 x = 0 ~ 199
    //         y = (WINDOW_HEIGHT - 200) ~ (WINDOW_HEIGHT - 1)
    //한칸에 20 x 20 픽셀로 표현
    //일단 map 표현 
    //빈칸은 검정
    //플레이어 위치는 빨간색
    //벽은 희색
    //방향,카메라 벡터 이용해서 ray 좌우 계산.(기존 레이 케스팅 활용해서 충돌 지점 계산) 
    //y = ((-dirY) / dirX ) * (x - locX) - (locY)
void    draw_map(t_player player, t_img img, t_map map)
{
    int i;
    int j;
    int px;
    int py;

    px = (int)(player.loc.x * 20);
    py = (int)(player.loc.y * 20);
    i = -1;
    while (++i < 220)
    {   
        j = -1;
        while (++j < 220)
            my_mlx_pixel_put(&img, j, i + (WIN_HEIGHT - 220), 0x00000000);                
    }
    i = -1;
    while (++i < 220)
    {
        if (py / 20 + i / 20 - 5 < 0 || py / 20 + i / 20 - 5 >= map.height)
            continue ;
        j = -1;
        while (++j < 220)
        {
            if (px / 20 + j / 20 - 5 < 0 || px / 20 + j / 20 - 5 >= map.width)
                continue ;
            if (map.board[py / 20 + i / 20 - 5][px / 20 + j / 20 - 5] == 1)//벽
                my_mlx_pixel_put(&img, j, i + (WIN_HEIGHT - 220), 0x00FFFFFF);
            else if (i / 20 == 5 && j / 20 == 5)//플레이어 위치
                my_mlx_pixel_put(&img, j, i + (WIN_HEIGHT - 220), 0x00FF0000);
        }
    }
}

void    print_img(t_game *game_info)
{
	make_img(game_info);
	draw_floor_ceil(game_info, 0x00000000, 0x00FF0000);
    //draw wall
    
	draw_map(game_info->player, game_info->img, game_info->map);
	mlx_put_image_to_window(game_info->mlx, game_info->win, game_info->img.img, 0, 0);
	if (game_info->img_copy)
		mlx_destroy_image(game_info->mlx, game_info->img_copy);
}