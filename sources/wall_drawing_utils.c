/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_drawing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 21:05:21 by heson             #+#    #+#             */
/*   Updated: 2023/08/03 18:34:18 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../headers/drawing_3d.h"

int	get_texture_x(t_vector player_loc, t_ray_data ray,
					double dist, int texture_width)
{
	double	wall_hitpoint_x;
	int		texture_x;

	if (ray.side == NS)
		wall_hitpoint_x = player_loc.y + (dist * ray.dir.y);
	else
		wall_hitpoint_x = player_loc.x + (dist * ray.dir.x);
	wall_hitpoint_x -= floor((wall_hitpoint_x));
	texture_x = (int)(wall_hitpoint_x * texture_width);
	if (ray.side == NS && ray.dir.x < 0)
		texture_x = texture_width - texture_x - 1;
	if (ray.side == WE && ray.dir.y > 0)
		texture_x = texture_width - texture_x - 1;
	return (texture_x);
}

t_img	get_texture_img(int hit_side, t_point hitpoint,
							t_map map, t_vector player_loc)
{
	if (map.board[hitpoint.y][hitpoint.x] == DOOR)
		return (map.door_texture);
	if (hit_side == NS)
	{
		if (hitpoint.x > player_loc.x)
			return (map.east_texture);
		else
			return (map.west_texture);
	}
	else
	{
		if (hitpoint.y < player_loc.y)
			return (map.north_texture);
		else
			return (map.south_texture);
	}
}

unsigned int	get_color(t_img img, int x, int y)
{
	char	*dst;

	dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
