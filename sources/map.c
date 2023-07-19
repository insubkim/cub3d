/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:25:23 by insub             #+#    #+#             */
/*   Updated: 2023/07/19 10:51:22 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/my_types.h"
#include "../library/libft/libft.h"

#include <stdio.h>
void    draw_map(t_game *game_info)
{
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

    char map[11][11] = {0,};
    for (int i = 0; i < 11; i++){
        for (int j = 0; j < 11; j++){
            if ((int)game_info->player.loc.y - 5 + i < 0 || (int)game_info->player.loc.x - 5 + j < 0)
                map[i][j] = '0';
            else if ((int)game_info->player.loc.y - 5 + i >= game_info->map.height || (int)game_info->player.loc.x - 5 + j >= game_info->map.width)
                map[i][j] = '0';
            else if (game_info->map.board[(int)game_info->player.loc.y - 5 + i][(int)game_info->player.loc.x - 5 + j] == 1)
                map[i][j] = '1';
            else
                map[i][j] = '0';
        }
    }
    map[5][5] = 'P';
    
}