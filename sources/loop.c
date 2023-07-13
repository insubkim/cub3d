/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:18:56 by inskim            #+#    #+#             */
/*   Updated: 2023/07/13 22:59:17 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/my_types.h"
#include "../library/mlx/mlx.h"

int     main(int argc, char **argv){
        t_game  game_info;
        // parse
        argc++;argv++;//avoid norminette error
        // init mlx
		game_info.mlx = mlx_init();
        // set window
        // set img
        // make floor ceil
        // raycast
        // mlx hook 
        //mlx_hook(game_info.win, 2, 0, handle_key, &game_info);// keyboard input handle
        //mlx_hook(game_info.win, 17, 0, handle_close, &game_info);// red closs handle
        mlx_loop(game_info.mlx);// 이미지 표현
        //free_game(game_info);// 힙 초기화
        return (0);
}