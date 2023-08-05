/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:25:23 by insub             #+#    #+#             */
/*   Updated: 2023/08/05 23:51:39 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	set_door(char **board, int x, int y)
{
	if (board[y][x] == DOOR_CLOSED || board[y][x] == DOOR_CLOSING)
		board[y][x] = DOOR_OPENING;
	else if (board[y][x] == DOOR_OPENED || board[y][x] == DOOR_OPENING)
		board[y][x] = DOOR_CLOSING;
}

void	handle_door(t_game *game_info)
{
	int	x;
	int	y;

	x = game_info->player.loc.x;
	y = game_info->player.loc.y;
	//padding 적용 해여함.
	set_door(game_info->map.board, x + 1, y);
	set_door(game_info->map.board, x - 1, y);
	set_door(game_info->map.board, x, y + 1);
	set_door(game_info->map.board, x, y - 1);
}
