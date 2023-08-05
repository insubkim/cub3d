/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 23:07:08 by heson             #+#    #+#             */
/*   Updated: 2023/08/05 14:50:03 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../headers/drawing_3d.h"

void	init_side_data_of_ray(t_side_data_of_ray *ray, int ray_loc,
									double ray_dir, double player_loc)
{
	ray->delta_dist = 1e30;
	if (ray_dir)
		ray->delta_dist = fabs(1 / ray_dir);
	if (ray_dir < 0)
	{
		ray->step_size = -1;
		ray->side_dist = (player_loc - (int)ray_loc) * ray->delta_dist;
	}
	else
	{
		ray->step_size = 1;
		ray->side_dist = ((int)ray_loc + 1.0 - player_loc) * ray->delta_dist;
	}
}

void	init_vars_for_raycasting(t_ray_data *ray, t_player player,
									double camera_x)
{
	ray->dir.x = player.dir.x + (player.plane.x * camera_x);
	ray->dir.y = -(player.dir.y + (player.plane.y * camera_x));
	ray->loc.x = player.loc.x;
	ray->loc.y = player.loc.y;
	init_side_data_of_ray(&(ray->x), ray->loc.x, ray->dir.x, player.loc.x);
	init_side_data_of_ray(&(ray->y), ray->loc.y, ray->dir.y, player.loc.y);
	ray->is_hit = 0;
}

static void	jump_to_next_side(int side, t_side_data_of_ray *side_data,
								int *ray_loc, int *ray_side)
{
	side_data->side_dist += side_data->delta_dist;
	*ray_loc += side_data->step_size;
	*ray_side = side;
}

int	is__hit(t_ray_data *ray, char **map_board, double **door_timer)
{
	double	dist;
	double	wall_dist;
	double	offset;

	if (ray->side == NS)
	{
		wall_dist = ray->y.side_dist;
		dist = (ray->x.side_dist - ray->x.delta_dist / 2);
		offset = floor(ray->loc.x + dist * cos(atan2(ray->dir.y, ray->dir.x)));
	}
	else
	{
		wall_dist = ray->x.side_dist;
		dist = (ray->y.side_dist - ray->y.delta_dist / 2);
		offset = floor(ray->loc.y + dist * cos(atan2(ray->dir.y, ray->dir.x)));
	}
	if (map_board[(int)ray->loc.y][(int)ray->loc.x] == DOOR && \
		dist < wall_dist && offset < fabs(door_timer[(int)ray->loc.y][(int)ray->loc.x]))
		return (TRUE); 
	return (FALSE);
}

double	get_dist_of_ray(t_ray_data *ray, char **map_board, double **door_timer)
{
	double		dist;
	int			is_hit;

	is_hit = FALSE;
	while (!is_hit)
	{
		if (ray->x.side_dist < ray->y.side_dist)
			jump_to_next_side(NS, &(ray->x), &(ray->loc.x), &(ray->side));
		else
			jump_to_next_side(WE, &(ray->y), &(ray->loc.y), &(ray->side));
		if (map_board[(int)ray->loc.y][(int)ray->loc.x] == WALL || \
			is_door_hit(ray, map_board, door_timer))
			is_hit = TRUE;
	}
	if (ray->side == NS)
		dist = (ray->x.side_dist - ray->x.delta_dist);
	else
		dist = (ray->y.side_dist - ray->y.delta_dist);
	if (is_door_hit(ray, map_board, door_timer))
	{
		if (ray->side == NS)
			dist += ray->x.delta_dist / 2;
		else
			dist += ray->y.delta_dist / 2;
	}	
	return (dist);
}
