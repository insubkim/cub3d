/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:25:23 by insub             #+#    #+#             */
/*   Updated: 2023/08/07 11:37:51 by inskim           ###   ########.fr       */
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
	if ((int)(x + 0.2) == (int)x)
		set_door(game_info->map.board, x + 1, y);
	if ((int)(x - 0.2) == (int)x)
		set_door(game_info->map.board, x - 1, y);
	if ((int)(y + 0.2) == (int)y)
		set_door(game_info->map.board, x, y + 1);
	if ((int)(y - 0.2) == (int)y)
		set_door(game_info->map.board, x, y - 1);
}

int	init_door_timer(t_game *game_info)
{
	int	i;
	int	j;

	game_info->map.door_timer = \
	ft_calloc(game_info->map.height, sizeof(double *));
	if (game_info->map.door_timer == ERROR_POINTER)
		return (FALSE);
	i = 0;
	while (i < game_info->map.height)
	{
		game_info->map.door_timer[i] = \
		ft_calloc(game_info->map.width, sizeof(double));
		j = -1;
		while (++j < game_info->map.width)
			game_info->map.door_timer[i][j] = 1;
		if (game_info->map.door_timer[i] == ERROR_POINTER)
			return (ERROR_INT);
		i++;
	}
	return (TRUE);
}

void	run_door_timer(t_game *game_info)
{
	int	i;
	int	j;

	i = 0;
	while (i < game_info->map.height)
	{
		j = 0;
		while (j < game_info->map.width)
		{
			if (game_info->map.board[i][j] == DOOR_CLOSING)
			{
				game_info->map.door_timer[i][j] += 0.1;
				if (game_info->map.door_timer[i][j] >= 1)
					game_info->map.board[i][j] = DOOR_CLOSED;
			}
			else if (game_info->map.board[i][j] == DOOR_OPENING)
			{
				game_info->map.door_timer[i][j] -= 0.1;
				if (game_info->map.door_timer[i][j] <= 0)
					game_info->map.board[i][j] = DOOR_OPENED;
			}
			j++;
		}
		i++;
	}
}
