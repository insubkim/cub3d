/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 12:40:12 by inskim            #+#    #+#             */
/*   Updated: 2023/07/29 21:52:30 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/mlx/mlx.h"
#include "../headers/my_types.h"
#include "../headers/drawing_3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);//test

/* draw_square
 * : point 부터 size 크기의 정사각형을 color 값으로 img에 넣음 
 * 
 * paramter - img: 이미지 정보
 *          - point: 시작 x,y 좌표
 *          - color: 픽셀 값
 *return: none
 */       
void	draw_square(t_img img, t_point point, int size, int color)
{
	int	i;
	int	j;

	i = point.y;
	while (i < point.y + size)
	{
		j = point.x;
		while (j < point.x + size)
		{
			my_mlx_pixel_put(&img, j, i, color);
			j++;
		}		
		i++;
	}
}

/* set_map_white
 * : 맵을 전부 흰색으로 세팅
 * parameter - img : 이미지 정보
 * return: none
 */
void	set_map_white(t_img img)
{
	t_point p;
	
	p.x = 0;
	p.y = WIN_HEIGHT - 220;
	draw_square(img, p, 220, 0x00FFFFFF);
}

/* draw_dir
 * : 플레이어 방향 벡터를 img에 표시함.
 * parameter - player: 플레이어 정보
 *           - img: mlx 이미지
 * return: none
 */
void	draw_dir(t_player player, t_img img)
{
    int i;
    double radian;

    i = 0;
    radian = atan2(-player.dir.y, player.dir.x);
    while (i < 30)
    {
        my_mlx_pixel_put(&img, cos(radian) * i + 100 , sin(radian) * i + 100 + (WIN_HEIGHT - 220), 0x00FF0000);		
        i++;
    }
}

/* draw_map
 * : 플레이어 위치에 따른 맵 생성. 맵 정중앙은 플레이어 위치이고 각 방향 5칸 까지의 구조물을 표현함. 
 *   한 칸당 20 * 20 픽셀로 나타냄. 맵은 220 * 220 펙셀임. 화면 왼쪽 하단에 표시
 * parameter - player: 플레이어 정보
 *           - img: mlx 이미지
 *           - map: 맵 정보
 * return: none
 */
void    draw_map(t_player player, t_img img, t_map map)
{
    int i;
    int j;
	t_point p;

	set_map_white(img);
    p.x = (int)(player.loc.x * 20);
    p.y = (int)(player.loc.y * 20);
    i = -1;
    while (++i < 220)
    {
        if (p.y + i - 100 < 0 || p.y + i - 100 >= map.height * 20)//맵 범위 넘어갔을시
            continue ;
        j = -1;
        while (++j < 220)
        {
            if (p.x + j - 100 < 0 || p.x + j - 100 >= map.width * 20)//맵 범위 넘어갔을시
                continue ;
            if (map.board[(p.y + i - 100) / 20][(p.x + j - 100) / 20] == WALL)
                my_mlx_pixel_put(&img, j, i + (WIN_HEIGHT - 220), 0x00808080);
            else if ((i - 100) * (i - 100) + (j - 100) * (j - 100) < 30)// 가운데는 플레이어 위치 표시
                my_mlx_pixel_put(&img, j, i + (WIN_HEIGHT - 220), 0x00FF0000);
        }
    }
    draw_dir(player, img);
}