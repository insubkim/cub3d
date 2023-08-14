/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heson <heson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:56:45 by heson             #+#    #+#             */
/*   Updated: 2023/08/11 13:38:51 by heson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d_bonus.h"

static int	is_possible_char(char ch, int is_player_found, int has_door)
{
	if (ch == '0' || ch == '1' || ch == ' ')
		return (TRUE);
	if (ch == '2')
		return (has_door);
	if (!is_player_found
		&& (ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W'))
		return (TRUE);
	return (FALSE);
}

static char	get_side_tile(int dir, t_map map, int w, int h)
{
	int	dir_h[4];
	int	dir_w[4];
	int	new_w;
	int	new_h;

	dir_h[UP] = -1;
	dir_h[RIGHT] = 0;
	dir_h[DOWN] = 1;
	dir_h[LEFT] = 0;
	dir_w[UP] = 0;
	dir_w[RIGHT] = 1;
	dir_w[DOWN] = 0;
	dir_w[LEFT] = -1;
	new_w = w + dir_w[dir];
	new_h = h + dir_h[dir];
	if (new_w < 0 || new_w >= map.width || new_h < 0 || new_h >= map.height)
		return (SPACE);
	return (map.board[new_h][new_w]);
}

static int	is_valid_wall(t_map map, int w, int h)
{
	int	dir;
	int	side_tile;
	int	type_cnt[3];

	type_cnt[0] = 0;
	type_cnt[1] = 0;
	type_cnt[2] = 0;
	dir = UP;
	while (dir < DIR_CNT)
	{
		side_tile = get_side_tile(dir, map, w, h);
		if (side_tile == WALL)
			type_cnt[WALL - '0']++;
		else if (side_tile == SPACE)
			type_cnt[2]++;
		else
			type_cnt[EMPTY - '0']++;
		dir++;
	}
	if (type_cnt[WALL - '0'] >= 2)
		return (TRUE);
	if (!type_cnt[2] || !type_cnt[EMPTY - '0'])
		return (TRUE);
	return (FALSE);
}

static int	is_valid_tile(char tile, int w, int h, t_map map)
{
	char	side_tile;

	if (tile == SPACE)
	{
		side_tile = get_side_tile(RIGHT, map, w, h);
		if (!(side_tile == SPACE || side_tile == WALL))
			return (FALSE);
		side_tile = get_side_tile(DOWN, map, w, h);
		if (!(side_tile == SPACE || side_tile == WALL))
			return (FALSE);
	}
	else if (tile == WALL)
		return (is_valid_wall(map, w, h));
	else
	{
		side_tile = get_side_tile(RIGHT, map, w, h);
		if (side_tile == SPACE)
			return (FALSE);
		side_tile = get_side_tile(DOWN, map, w, h);
		if (side_tile == SPACE)
			return (FALSE);
	}
	return (TRUE);
}

int	is_valid_map(t_map *map, t_vector *player_loc, char *player_dir)
{
	int	h;
	int	w;

	h = -1;
	while (++h < map->height)
	{
		w = -1;
		while (++w < map->width)
		{
			if (!is_possible_char(map->board[h][w], *player_dir,
				map->door_texture.img != NULL))
				return (print_error(ERROR_IMPOSSIBLE_CHAR, FALSE));
			if (!is_valid_tile(map->board[h][w], w, h, *map))
				return (print_error(ERROR_INVALID_MAP, FALSE));
			if (map->board[h][w] != SPACE && map->board[h][w] != WALL
				&& map->board[h][w] != EMPTY && map->board[h][w] != DOOR_CLOSED)
			{
				player_loc->x = w + 0.2;
				player_loc->y = h + 0.2;
				*player_dir = map->board[h][w];
			}
		}
	}
	return (TRUE);
}
