/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:03:37 by heson             #+#    #+#             */
/*   Updated: 2023/08/03 18:04:33 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

static int	init_map_board(t_list *list_p, t_map *map)
{
	int		h;
	int		w;
	char	*p;

	map->board = (char **)malloc(sizeof(char *) * map->height);
	if (!map->board)
		return (free_map(&(map->board), 0));
	h = -1;
	while (++h < map->height)
	{
		map->board[h] = (char *)ft_calloc(map->width, sizeof(char));
		if (!map->board[h] || !list_p || !(char *)(list_p->content))
			return (free_map(&(map->board), h));
		p = (char *)list_p->content;
		w = -1;
		while (++w < map->width)
		{
			if (*p)
				map->board[h][w] = *p++;
			else
				map->board[h][w] = ' ';
		}
		list_p = list_p->next;
	}
	return (SUCCESS);
}

static void	init_player(t_player *player, t_vector loc, char dir)
{
	player->loc = loc;
	player->dir.x = 0;
	player->dir.y = 0;
	player->plane.x = 0;
	player->plane.y = 0;
	if (dir == 'N')
	{
		player->plane.x = 0.66;
		player->dir.y = 1;
	}
	else if (dir == 'S')
	{
		player->plane.x = -0.66;
		player->dir.y = -1;
	}
	else if (dir == 'E')
	{
		player->dir.x = 1;
		player->plane.y = -0.66;
	}
	else if (dir == 'W')
	{
		player->dir.x = -1;
		player->plane.y = 0.66;
	}
}

int	map_parsing(t_list *target, t_game *game_data)
{
	t_vector	player_loc;
	char		player_dir;

	if (init_map_board(target, &(game_data->map)) == ERROR_INT)
		return (ERROR_INT);
	player_dir = 0;
	if (!is_valid_map(&(game_data->map), &player_loc, &player_dir))
		return (free_map(&(game_data->map.board), game_data->map.height));
	if (!player_dir)
	{
		free_map(&(game_data->map.board), game_data->map.height);
		return (print_error(ERROR_NO_PLAYER, ERROR_INT));
	}
	init_player(&(game_data->player), player_loc, player_dir);
	return (SUCCESS);
}
