/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:44:03 by heson             #+#    #+#             */
/*   Updated: 2023/08/07 11:35:39 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	move_dir(enum e_direction dir, t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_rate;

	if (dir == LEFT)
		rot_rate = ROTATE_DEGREE * PI / 180;
	else
		rot_rate = -ROTATE_DEGREE * PI / 180;
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(rot_rate) \
			- player->dir.y * sin(rot_rate);
	player->dir.y = old_dir_x * sin(rot_rate) + player->dir.y * cos(rot_rate);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(rot_rate) \
			- player->plane.y * sin(rot_rate);
	player->plane.y = old_plane_x * sin(rot_rate) \
			+ player->plane.y * cos(rot_rate);
}

static int	is_not_tile_type(char **board, double x, double y, \
	enum e_tile_type tile_type)
{
	double	padding;

	padding = (double)1 / TILESIZE;
	if (board[(int)y][(int)x] != (char)tile_type
		&& board[(int)y][(int)(x + padding)] != (char)tile_type
		&& board[(int)y][(int)(x - padding)] != (char)tile_type
		&& board[(int)(y - padding)][(int)x] != (char)tile_type
		&& board[(int)(y - padding)][(int)(x + padding)] != (char)tile_type
		&& board[(int)(y - padding)][(int)(x - padding)] != (char)tile_type
		&& board[(int)(y + padding)][(int)x] != (char)tile_type
		&& board[(int)(y + padding)][(int)(x + padding)] != (char)tile_type
		&& board[(int)(y + padding)][(int)(x - padding)] != (char)tile_type)
		return (TRUE);
	return (FALSE);
}

void	move_player(enum e_direction dir, t_game *game_info, \
				char **board, t_vector loc)
{
	double	radian;
	double	x;
	double	y;

	if (dir == UP || dir == DOWN)
		radian = atan2(-game_info->player.dir.y, game_info->player.dir.x);
	else
		radian = atan2(-game_info->player.plane.y, game_info->player.plane.x);
	x = cos(radian) * ((double)1 / TILESIZE);
	y = sin(radian) * ((double)1 / TILESIZE);
	if (dir == DOWN || dir == LEFT)
	{
		x *= -1;
		y *= -1;
	}
	if (is_not_tile_type(board, x + loc.x, y + loc.y, WALL) && \
		is_not_tile_type(board, x + loc.x, y + loc.y, DOOR_CLOSED) && \
		is_not_tile_type(board, x + loc.x, y + loc.y, DOOR_CLOSING))
	{
		game_info->player.move_offset.x = x / SPRITE_NUM;
		game_info->player.move_offset.y = y / SPRITE_NUM;
		game_info->sprite = 0;
	}
}
