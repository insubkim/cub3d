/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:18:56 by inskim            #+#    #+#             */
/*   Updated: 2023/07/12 19:41:26 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/mlx"



int	main(void){
	t_game	game_info;
	//parse + init t_game

	//raycast

	//hook 
	mlx_hook(game_info->mlx_info -> window, 2, 0, handle_key, &game_info);
	mlx_hook(game_info->mlx_info -> window, 17, 0, handle_close, &game_info);
	mlx_loop(game_info->mlx_info -> mlx);
	free_game(game_info);
	return (0);
}