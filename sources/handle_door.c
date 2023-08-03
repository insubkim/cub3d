/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:25:23 by insub             #+#    #+#             */
/*   Updated: 2023/08/03 18:21:29 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	set_door(char **board, int x, int y)
{
	if (board[y][x] == DOOR)
		board[y][x] = DOOR_CLOSE;
	else if (board[y][x] == DOOR_CLOSE)
		board[y][x] = DOOR;
}

void	handle_door(t_game *game_info)
{
	int	x;
	int	y;

	x = game_info->player.loc.x;
	y = game_info->player.loc.y;
	set_door(game_info->map.board, x + 1, y);
	set_door(game_info->map.board, x - 1, y);
	set_door(game_info->map.board, x, y + 1);
	set_door(game_info->map.board, x, y - 1);
}