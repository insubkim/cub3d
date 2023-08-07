/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:25:23 by insub             #+#    #+#             */
/*   Updated: 2023/08/06 13:31:05 by insub            ###   ########.fr       */
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
	double	x;
	double	y;

	x = game_info->player.loc.x;
	y = game_info->player.loc.y;
	if ((int)(x + 0.2) == (int)x)//검증 안함.
		set_door(game_info->map.board, x + 1, y);
	if ((int)(x - 0.2) == (int)x)
		set_door(game_info->map.board, x - 1, y);
	if ((int)(y + 0.2) == (int)y)
		set_door(game_info->map.board, x, y + 1);
	if ((int)(y - 0.2) == (int)y)
		set_door(game_info->map.board, x, y - 1);
}
